#include "NonChassisSystems/flywheel.h"
#include "Config/other-config.h"
#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/intakes.h"
#include <mutex>

namespace Scorer {

// We have mutex becuase we have three tasks reading and writing to the same data
// Having these mutexes helps us avoid race conditions
static mutex scoreLock;
static mutex outyLock;


bool FlywheelStopWhenTopDetected = false;

bool Scored = false;

int flywheelTask() {


  bool ballEjected = false;

  // We dont want to stop the flywheel as soon as a ball exits because we stil need momentum. Therefore, we have timers that activate once the ball leaves

  math3142a::TimeoutTimer scoreTimeout(10,1250);

  math3142a::TimeoutTimer ejectorTimeout(10,1000);


  while (true) {


      if (FlywheelStopWhenTopDetected) {
         // index the ball up to the top line sensor
        LOG("FLYWHEEL INDEXING TO TOP LINE", topLine.value(analogUnits::range10bit), TOP_LINE_THRESHOLD);
        if (topLine.value(analogUnits::range10bit) < TOP_LINE_THRESHOLD) {
          LOG("BALL AT TOP"); // if the line sensor detects stop the flywheel
          Flywheel.spin(fwd, FLYWHEEL_STOP_VOLTAGE, volt);
        } else { // if it hasnt detected then run them
          Flywheel.spin(fwd, 9, volt);
        }
      }
      if (atGoal) {
        LOG("AT GOAL");

        FlywheelStopWhenTopDetected = false; //turn off the top line macro. these two are mutually exclusive

        if (!Scored) { // run while we havent scored a ball
          Flywheel.spin(fwd, SCORE_VOLTAGE, volt);
          LOG("SCORING",topLine.value(analogUnits::range10bit), TOP_LINE_EMPTY_THRESHOLD);
          if (topLine.value(analogUnits::range10bit) > TOP_LINE_EMPTY_THRESHOLD) { //if the top line is empty then we can start the timeout to stop intake

            scoreTimeout.m_currentTime += scoreTimeout.m_delay; //10 because it is the delay time
            LOG("SCORED");
            scoreLock.lock(); //lock the mutex as we are accessing the "scored" bool that is used in mutiple threads

            if (scoreTimeout.m_currentTime > scoreTimeout.m_timeout) { //once we have delayed for long enough, we have scored
              LOG("DONE SCORING"); 
              Scored = true;
            }
            scoreLock.unlock(); //unlock mutex
          }

        }

        else { // if we have scored (eject code)

          LOG("EJECTING",outyLine.value(analogUnits::range10bit),OUTY_LINE_THRESHOLD);
          Flywheel.spin(fwd, FLYWHEEL_OUTY_VOLTAGE, volt); //spin flywheel to reverse

          if (outyLine.value(analogUnits::range10bit) < OUTY_LINE_THRESHOLD) {
             //very similar "timeout" procedure as the scoring macro
            LOG("EJECTED BALL DETECTED");
            ballEjected = true;
          }

          if (ballEjected) {
            LOG("BALL EJECTED",ejectorTimeout.m_currentTime , ejectorTimeout.m_timeout);

            ejectorTimeout.m_currentTime += ejectorTimeout.m_delay; //increment timer by a delay

            outyLock.lock();

            if (ejectorTimeout.m_currentTime > ejectorTimeout.m_timeout) { // if we have elasped enough time since first ejected ball detection, we have outied
              LOG("DONE EJECTING and FINSIHED GOAL TASK");
              atGoal = false;
              Flywheel.spin(fwd,FLYWHEEL_STOP_VOLTAGE,volt);
              Intakes::backUp = true; //reverse intakes for a smooth exit
              Rollers::IndexerStop = true; //stop indexing

              // reset bools and timers for next goal sequence
              ballEjected = false;
              Scored = false;
              scoreTimeout.reset();
              ejectorTimeout.reset();

            }
            outyLock.unlock(); //unlock mutex for next run
          } // outy timeout
           // outy
      }     // at Goal

    } // not manual

    task::sleep(10);

  } // while true

} // function def

} // namespace scorer