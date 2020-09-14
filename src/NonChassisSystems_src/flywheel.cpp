#include "NonChassisSystems/flywheel.h"
#include "Config/other-config.h"
#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/intakes.h"
#include <mutex>

namespace Scorer {

static mutex scoreLock;
static mutex outyLock;

bool outy = false;


int flywheelTask(void* toBeCastedBools) {

  globalBools* instance = static_cast<globalBools*>(toBeCastedBools);

  bool ballOutied = false;

  math3142a::TimeoutTimer scoreTimeout(10,1000);

  math3142a::TimeoutTimer ejectorTimeout(10,1000);


  while (true) {
    if (outy) {
      Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt);
    }

    else {

      if (instance->FlywheelStopWhenTopDetected) { // index the ball up to the top line sensor
        if (topLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) { // if the line sensor detects stop the flywheel
          Flywheel.spin(fwd, FLYWHEEL_STOP_VOLTAGE, volt);
        } else { // if it hasnt detected then run them
          Flywheel.spin(fwd, SCORE_VOLTAGE, volt);
        }
      }
      if (atGoal) {
        LOG("AT GOAL");

        instance->FlywheelStopWhenTopDetected = false; //turn off the top line macro. these two are mutually exclusive

        if (!instance->scored) { // run while we havent scored a ball
          Flywheel.spin(fwd, SCORE_VOLTAGE, volt);
          LOG("SCORING",topLine.value(analogUnits::range10bit), TOP_LINE_EMPTY_THRESHOLD);
          if (topLine.value(analogUnits::range10bit) > TOP_LINE_EMPTY_THRESHOLD) { //if the top line is empty then we can start the timeout to stop intake

            scoreTimeout.m_currentTime += scoreTimeout.m_delay; //10 because it is the delay time
            LOG("SCORED");
            scoreLock.lock(); //lock the mutex as we are accessing the "scored" bool that is used in mutiple threads

            if (scoreTimeout.m_currentTime > scoreTimeout.m_timeout) {
              LOG("DONE SCORING"); 
              instance->scored = true;
            }
            scoreLock.unlock(); //unlock mutex
          }

        }

        else { // if we have scored (;eject code)

          LOG("EJECTING",outyLine.value(analogUnits::range10bit),OUTY_LINE_THRESHOLD);
          Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt); //spin flywheel to reverse

          if (outyLine.value(analogUnits::range10bit) < OUTY_LINE_THRESHOLD) {
             //very similar "timeout" procedure as the scoring macro
            LOG("EJECTED BALL DETECTED");
            ballOutied = true;
          }

          if (ballOutied) {
            LOG("BALL EJECTED",ejectorTimeout.m_currentTime , ejectorTimeout.m_timeout);

            ejectorTimeout.m_currentTime += ejectorTimeout.m_delay;

            outyLock.lock();

            if (ejectorTimeout.m_currentTime > ejectorTimeout.m_timeout) { // if we have elasped enough time since first ejected ball detection, we have outied
              LOG("DONE EJECTING and FINSIHED GOAL TASK");
              atGoal = false;
              Flywheel.spin(fwd,FLYWHEEL_STOP_VOLTAGE,volt);
              instance->backUp = true;
              //instance->FlywheelStopWhenTopDetected = true;

              // reset bools and timers for next goal sequence
              ballOutied = false;
              instance->scored = false;
              scoreTimeout.reset();
              ejectorTimeout.reset();

            }
            outyLock.unlock();
          } // outy timeout
        }   // outy
      }     // at Goal

    } // not manual

    task::sleep(10);

  } // while true

} // function def

void outyTask() { Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt); }

} // namespace Scorer