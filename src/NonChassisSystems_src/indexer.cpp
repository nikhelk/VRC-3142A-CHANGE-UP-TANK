#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/flywheel.h"
#include <iostream>

namespace Rollers {



int indexerTask(void* toBeCastedBools) {

  globalBools* instance = static_cast<globalBools*>(toBeCastedBools);

  instance->resetBools();
  while (true) {
    if (instance->IndexerStopWhenTopDetected) {  // Stop indexer when top line detects ball

      //reset the other ones

      instance->IndexerStopWhenMiddleDetected = false;
      instance->IndexerStopWhenBottomDetected = false;
      instance->IndexerRunContinuously = false;

      if (middleLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
        LOG(" Top Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt); //stop when detected
      } else {
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }

    if (instance->IndexerStopWhenMiddleDetected) { // similar to StopWhenTopDetected but for the middle line sensor
      if (middleLine.value(analogUnits::range10bit) < MIDDLE_LINE_THRESHOLD) {
        LOG(" Middle Ball detected");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);
      } else {
        Indexer.spin(fwd, INDEXER_OUTY_VOLTAGE, volt);
      }
    }
    if (instance->IndexerStopWhenBottomDetected) { // similar to StopWhenTopDetected but for the bottom line sensor
      if (bottomLine.value(analogUnits::range10bit) < BOTTOM_LINE_THRESHOLD) {
        LOG("ball at bottom");
        Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);

      } else {
        Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
      }
    }
    if (instance->IndexerRunContinuously) { // keep running indexer
      Indexer.spin(fwd, INDEXER_VOLTAGE, volt);
    }
    if (instance->IndexerStop) {
      instance->FlywheelStopWhenTopDetected = false;
      instance->IndexerStopWhenMiddleDetected = false;
      instance->IndexerStopWhenBottomDetected = false;
      instance->IndexerRunContinuously = false;

      Indexer.spin(fwd, INDEXER_STOP_VOLTAGE, volt);

    }

    if (atGoal) {

      instance->IndexerRunContinuously = false;
      instance->IndexerStopWhenTopDetected = false;
      instance->IndexerStopWhenBottomDetected = false;

      if (!instance->scored) { // index to the middle while flywheel is scoring
        instance->IndexerStopWhenMiddleDetected = true;
      } else { // run ejector
        instance->IndexerStopWhenMiddleDetected = false;
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