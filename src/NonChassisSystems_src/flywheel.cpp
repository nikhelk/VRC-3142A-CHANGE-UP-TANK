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

      if (FlywheelStopWhenTopDetected) { // index the ball up to the top line sensor
        if (topLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) { // if the line sensor detects stop the flywheel
          Flywheel.spin(fwd, FLYWHEEL_STOP_VOLTAGE, volt);
        } else { // if it hasnt detected then run them
          Flywheel.spin(fwd, SCORE_VOLTAGE, volt);
        }
      }
      if (atGoal) {

        FlywheelStopWhenTopDetected = false; //turn off the top line macro

        if (!scored) { // run while we havent scored a ball
          Flywheel.spin(fwd, SCORE_VOLTAGE, volt);

          if (topLine.value(analogUnits::range10bit) > TOP_LINE_EMPTY_THRESHOLD) { //if the top line is empty then we can start the timeout to stop intake

            scoreTimeoutTimer += 10; //10 because it is the delay time

            scoreLock.lock(); //lock the mutex as we are accessing the "scored" bool that is used in mutiple threads

            if (scoreTimeoutTimer > 1000) {

              scored = true;
            }
            scoreLock.unlock(); //unlock mutex
          }

        }

        else { // if we have scored (eject code)

          Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt); //spin flywheel to reverse

          if (outyLine.value(analogUnits::range10bit) < OUTY_LINE_THRESHOLD) { //very similar "timeout" procedure as the scoring macro

            ballOutied = true;
          }

          if (ballOutied) {

            outyTimeoutTimer += 10;

            outyLock.lock();

            if (outyTimeoutTimer > 1000) { // if we have elasped enough time since first ejected ball detection, we have outied

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