#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/flywheel.h"
#include <iostream>

namespace Rollers {

bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected = false;
bool IndexerStopWhenBottomDetected = false;
bool IndexerRunContinuously = false;

int indexerTask() {

  while (true) {
    if (IndexerStopWhenTopDetected) {
      if (middleLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
        LOG(" Top Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);
      } else {
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }

    if (IndexerStopWhenMiddleDetected) {
      if (middleLine.value(analogUnits::range10bit) < MIDDLE_LINE_THRESHOLD) {
        LOG(" Middle Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);
      } else {
        Indexer.spin(fwd, INDEXER_OUTY_VOLTAGE, volt);
      }
    }
    if (IndexerStopWhenBottomDetected) {
      if (bottomLine.value(analogUnits::range10bit) < BOTTOM_LINE_THRESHOLD) {
        LOG("ball at bottom");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);

      } else {
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }
    if (IndexerRunContinuously) {
      Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
    }

    if (atGoal) {

      IndexerRunContinuously = false;
      IndexerStopWhenTopDetected = false;
      IndexerStopWhenBottomDetected = false;

      if (!Scorer::scored) { // index to the middle while flywheel is scoring
        IndexerStopWhenMiddleDetected = true;
      } else { // run outy
        IndexerStopWhenMiddleDetected = false;
        Indexer.spin(fwd, INDEXER_OUTY_VOLTAGE, volt);
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