#include "NonChassisSystems/flywheel.h"
#include "Config/other-config.h"
#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/intakes.h"
bool startFlyDecel = false;
bool outy =false;
bool doOuty = false;
bool doOuty2 = false;
bool FlywheelStopWhenTopDetected = false;
bool scored = false;
double scoreTimer = 0;
int flywheelTask()
{
  double start = Brain.timer(timeUnits::sec);
  while (true)
  {
    if(outy) {
       Flywheel.spin(fwd, -12, volt);
    }

    else {
      if(FlywheelStopWhenTopDetected) {
        if(topLine.value(analogUnits::range10bit) < 711) {
          Flywheel.spin(fwd,0,volt);
        }
        else {
          Flywheel.spin(fwd,10,volt);
        }
      }
      if(atGoal) {

        FlywheelStopWhenTopDetected = false;
        while(!scored) {
        Flywheel.spin(fwd,12,volt);
        if(topLine.value(analogUnits::range10bit) >720) {

           double currTime =  Brain.timer(timeUnits::sec) -start;
           if(currTime > 3) {
             scored = true;

             //doOuty2 = true;
             
           }

        }
        task::sleep(3);
      }
      bool outied = false;
      IndexerStopWhenMiddleDetected = false;
      bool startOutyTimer = false;

      while(!outied) {
      

      Flywheel.spin(fwd, -12, volt);
      
      //Indexer.spin(fwd, 6, volt);


      if(outyLine.value(analogUnits::range10bit) < 700) {

        startOutyTimer =  true;

      }

      if(startOutyTimer) {
          
          outied = true;
        }



      task::sleep(3);

      }
      
      atGoal = false;
      backUp = true;
      FlywheelStopWhenTopDetected = true;

      }
      else {
        Flywheel.spin(fwd,0,volt);
      }
    task::sleep(5);
  }
  }
}

void outyTask()
{
  Flywheel.spin(fwd, -12, volt);
}