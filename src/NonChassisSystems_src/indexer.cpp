#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/flywheel.h"
#include <iostream>

namespace Rollers {

bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected = false;
bool IndexerStopWhenBottomDetected = false;
bool IndexerRunContinuously = false;

static constexpr int INDEXER_VOLTAGE = 12;

static constexpr int STOP_VOLTAGE = 0;

static constexpr int EJECT_VOLTAGE = -8;

static constexpr int BOTTOM_LINE_THRESHOLD = -8;

static constexpr int MIDDLE_LINE_THRESHOLD = -8;

static constexpr int TOP_LINE_THRESHOLD = 711;

static constexpr int OUTY_LINE_THRESHOLD = -8;

int indexerTask() {

  while (true) {
    if (IndexerStopWhenTopDetected) {
      if (middleLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
        LOG(" Top Ball detected");
        Indexer.spin(fwd, 0, volt);
      } else {
        Indexer.spin(fwd, INDEXER_VOLTAGE , volt);
      }
    }

    if (IndexerStopWhenMiddleDetected) {
      if (middleLine.value(analogUnits::range10bit) < 697) {
        LOG(" Middle Ball detected");
        Indexer.spin(fwd, 0, volt);
      } else {
        Indexer.spin(fwd, 7, volt);
      }
    }
    if (IndexerStopWhenBottomDetected) {
      if (bottomLine.value(analogUnits::range10bit) < 695) {
        LOG("ball at bottom");
        Indexer.spin(fwd, 0, volt);

      } else {
        Indexer.spin(fwd, 10, volt);
      }
    }
    if (IndexerRunContinuously) {
      Indexer.spin(fwd, 12, volt);
    }

    if (atGoal) {

      IndexerRunContinuously = false;
      IndexerStopWhenTopDetected = false;
      IndexerStopWhenBottomDetected = false;

      if (!Scorer::scored) { // index to the middle while flywheel is scoring
        IndexerStopWhenMiddleDetected = true;
      } else { // run outy
        IndexerStopWhenMiddleDetected = false;
        Indexer.spin(fwd, 600 * .5, velocityUnits::rpm);
      }
    }

    task::sleep(5);
  }
}

void stopIndexerTask(task taskID) {
  taskID.suspend();
  Indexer.spin(fwd, 0, volt);
}

}