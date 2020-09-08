#include "NonChassisSystems/flywheel.h"
#include "Config/other-config.h"
#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/intakes.h"
#include <mutex>

namespace Scorer {

static mutex scoreLock;
static mutex outyLock;

bool outy = false;

bool FlywheelStopWhenTopDetected = false;

bool scored = false;

int flywheelTask() {
  bool ballOutied = false;
  double scoreTimeoutTimer = 0;
  double outyTimeoutTimer = 0;

  while (true) {
    if (outy) {
      Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt);
    }

    else {

      if (FlywheelStopWhenTopDetected) {
        if (topLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
          Flywheel.spin(fwd, FLYWHEEL_STOP_VOLTAGE, volt);
        } else {
          Flywheel.spin(fwd, SCORE_VOLTAGE, volt);
        }
      }
      if (atGoal) {

        FlywheelStopWhenTopDetected = false;

        if (!scored) {
          Flywheel.spin(fwd, SCORE_VOLTAGE, volt);

          if (topLine.value(analogUnits::range10bit) >
              TOP_LINE_EMPTY_THRESHOLD) {

            scoreTimeoutTimer += 10;

            scoreLock.lock();

            if (scoreTimeoutTimer > 1000) {

              scored = true;
            }
            scoreLock.unlock();
          }

        }

        else { // if we have scored (outy code)

          Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt);

          if (outyLine.value(analogUnits::range10bit) < OUTY_LINE_THRESHOLD) {

            ballOutied = true;
          }

          if (ballOutied) {

            outyTimeoutTimer += 10;

            outyLock.lock();

            if (outyTimeoutTimer >
                1000) { // if we have elasped enough time since first outy
                        // detection, we have outied

              atGoal = false;
              Intakes::backUp = true;
              FlywheelStopWhenTopDetected = true;

              // reset bools and timers for next goal sequence
              ballOutied = false;
              scored = false;
              scoreTimeoutTimer = 0;
              outyTimeoutTimer = 0;
            }
            outyLock.unlock();
          } // outy timeout
        }   // outy
      }     // at Goa;

    } // not manual

    task::sleep(10);

  } // while true

} // function def

void outyTask() { Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt); }

} // namespace Scorer