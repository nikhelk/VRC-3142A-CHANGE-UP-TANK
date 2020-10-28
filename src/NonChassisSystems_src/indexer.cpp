#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/flywheel.h"
#include <iostream>

namespace Rollers {

bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected= false;

bool IndexerRunContinuously = false;
bool IndexerStop = false;

int indexerTask() {

  while (true) {
    if (IndexerStopWhenTopDetected) {  // Stop indexer when top line detects ball

      


      if (topLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
        LOG(" Top Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt); //stop when detected
      } else { //run Indexer as long as we ghaven't detected anything
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }

    if (IndexerStopWhenMiddleDetected) {// similar to StopWhenTopDetected but for the middle line sensor
    IndexerStop = false;
      LOG("INDEXING TO MIDDLE SENSOR");
      if (middleLine.value(analogUnits::range10bit) < MIDDLE_LINE_THRESHOLD) {
        LOG(" Middle Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);
      } else {
        Indexer.spin(fwd, 12, volt);
      }
    }

    if (IndexerRunContinuously) { // keep running indexer at full speed
  

      Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
    }
    if (IndexerStop) { //stop indexer
      LOG("STOPPING INDEXER");


      Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);

    }

    if (atGoal) {

      IndexerRunContinuously = false;
      IndexerStopWhenTopDetected = false;
      IndexerStopWhenMiddleDetected = false;
      IndexerStop = false;

      if (!Scorer::Scored) { // index to the middle while flywheel is scoring
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      } else { // run ejector
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }

    task::sleep(10);
  }
}

void stopIndexerTask(task taskID) {
  taskID.suspend();
  Indexer.spin(fwd, 0, volt);
}

} // namespace Rollers