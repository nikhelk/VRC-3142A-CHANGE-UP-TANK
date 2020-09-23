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

      IndexerStopWhenMiddleDetected = false;
      IndexerStopWhenBottomDetected = false;
      IndexerRunContinuously = false;
      IndexerStop = false;

      if (topLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
        LOG(" Top Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt); //stop when detected
      } else {
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }

    if (IndexerStopWhenMiddleDetected) {// similar to StopWhenTopDetected but for the middle line sensor
      LOG("INDEXING TO MIDDLE SENSOR");
      if (middleLine.value(analogUnits::range10bit) < MIDDLE_LINE_THRESHOLD) {
        LOG(" Middle Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);
      } else {
        Indexer.spin(fwd, INDEXER_OUTY_VOLTAGE, volt);
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
      IndexerStopWhenTopDetected = false;
      IndexerStopWhenMiddleDetected = false;
      IndexerStopWhenBottomDetected = false;
      IndexerStop = false;

      Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
    }
    if (IndexerStop) {
      IndexerStopWhenTopDetected = false;
      IndexerStopWhenMiddleDetected = false;
      IndexerStopWhenBottomDetected = false;
      IndexerRunContinuously = false;

      Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);

    }

    if (atGoal) {

      IndexerRunContinuously = false;
      IndexerStopWhenTopDetected = false;
      IndexerStopWhenBottomDetected = false;
      IndexerStop = false;

      if (!Scorer::Scored) { // index to the middle while flywheel is scoring
        IndexerStopWhenMiddleDetected = true;
      } else { // run ejector
        IndexerStopWhenMiddleDetected = false;
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