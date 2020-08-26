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
    if(outy)
       Flywheel.spin(fwd, -12, volt);

    else if(doOuty2) {
      if(middleLine.value(analogUnits::range10bit) < 697) {
      Flywheel.spin(fwd, -12, volt);
      //Indexer.spin(fwd, 6, volt);
      Indexer.spin(fwd, 600*.5, velocityUnits::rpm);

      }
      else {
      Flywheel.spin(fwd, 0, volt);

      }

    }
    else if(doOuty) {
      int countOuty =0;
      
      int countEmpty =0;
      if(middleLine.value(analogUnits::range10bit) < 680) {

      while(countOuty<2) {
        Indexer.spin(fwd,7,volt);
        
        while(countEmpty == 0) {
          Indexer.spin(fwd,7,volt);
        Flywheel.spin(fwd, -12, volt);
        if(outyLine.value(analogUnits::range10bit) < 710) { 
          countOuty =1;
        }
        if(outyLine.value(analogUnits::range10bit) > 720) { 
          countEmpty =1;
        }
        }
        while(middleLine.value(analogUnits::range10bit) < 697) {
          Indexer.spin(fwd,7,volt);
        }
        while(countEmpty == 1) {
          Indexer.spin(fwd,7,volt);
          Flywheel.spin(fwd, -12, volt);
        if(outyLine.value(analogUnits::range10bit) < 710) { 
          countOuty =2;
        }
        if(outyLine.value(analogUnits::range10bit) > 720) { 
          countEmpty =2;

        }

      }

        }

      std::cout << countOuty <<std::endl;

      doOuty = false;

    }
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
      if(Goal1.atGoal) {
        int countScored =0;
        while(!scored) {
        Flywheel.spin(fwd,12,volt);
        if(topLine.value(analogUnits::range10bit) >720) {
          
          countScored =1;
           double currTime =  Brain.timer(timeUnits::sec) -start;
           if(currTime > 3) {
             scored = true;
             Goal1.atGoal = false;
             doOuty2 = true;
             backUp = true;
           }

        }
        task::sleep(3);
      }
      Flywheel.spin(fwd,0,volt);

      }
      else {
        Flywheel.spin(fwd,12,volt);
      }
    task::sleep(5);
  }
  }
}

void outyTask()
{
  Flywheel.spin(fwd, -12, volt);
}