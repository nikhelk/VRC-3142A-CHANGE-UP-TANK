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

static constexpr int SCORE_VOLTAGE = 10;

static constexpr int STOP_VOLTAGE = 0;

static constexpr int EJECT_VOLTAGE = -12;

static constexpr int TOP_LINE_THRESHOLD = 711;

int flywheelTask() {
  bool ballOutied = false;
  double scoreTimeoutTimer = 0;
  double outyTimeoutTimer = 0;

  while (true) {
    if (outy) {
      Flywheel.spin(fwd, -12, volt);
    }

    else {
      
      if (FlywheelStopWhenTopDetected) {
        if (topLine.value(analogUnits::range10bit) < 711) {
          Flywheel.spin(fwd, 0, volt);
        } else {
        Flywheel.spin(fwd, SCORE_VOLTAGE , volt);
        }
      }
      if (atGoal) {

        FlywheelStopWhenTopDetected = false;

        if (!scored) {
          Flywheel.spin(fwd, 12, volt);

          if (topLine.value(analogUnits::range10bit) > 720) {

            scoreTimeoutTimer += 5;

            scoreLock.lock();

            if (scoreTimeoutTimer > 1000) {

              scored = true;
            }
            scoreLock.unlock();
          }

        }

        else { // if we have scored (outy code)

          Flywheel.spin(fwd, -12, volt);

          if (outyLine.value(analogUnits::range10bit) < 700) {

            ballOutied = true;
          }

          if (ballOutied) {

            outyTimeoutTimer += 5;

            outyLock.lock();

            if (outyTimeoutTimer > 1000) {

              atGoal = false;
              Intakes::backUp = true;
              FlywheelStopWhenTopDetected = true;
            }
            outyLock.unlock();
          } // outy timeout
        } //outy
      } //at Goa;

    } //not manual

    task::sleep(5);

  } // while true

} // function def

void outyTask() { Flywheel.spin(fwd, -12, volt); }

}