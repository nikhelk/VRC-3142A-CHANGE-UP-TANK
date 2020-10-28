#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/flywheel.h"
#include <iostream>

namespace Rollers {

bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected= false;
bool IndexerStopWhenBottomDetected = false;
bool IndexerRunContinuously = false;
bool IndexerStop = false;

int indexerTask() {

  while (true) {
    if (IndexerStopWhenTopDetected) {  // Stop indexer when top line detects ball

      //reset the other ones
      LOG("INDEXING TO TOP SENSOR");



      if (topLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
        LOG(" Top Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt); //stop when detected
      } else {
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
    if (IndexerStopWhenBottomDetected) { // similar to StopWhenTopDetected but for the bottom line sensor
      if (bottomLine.value(analogUnits::range10bit) < BOTTOM_LINE_THRESHOLD) {
        LOG("ball at bottom");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);

      } else {
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }
    if (IndexerRunContinuously) { // keep running indexer
  

      Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
    }
    if (IndexerStop) {
      LOG("STOPPING INDEXER");


      Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);

    }

    if (atGoal) {

      IndexerRunContinuously = false;
      IndexerStopWhenTopDetected = false;
      IndexerStopWhenBottomDetected = false;
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