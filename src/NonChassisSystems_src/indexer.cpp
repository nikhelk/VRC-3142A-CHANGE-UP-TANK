#include "NonChassisSystems/indexer.h"
#include <iostream>


bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected = false;
bool IndexerStopWhenBottomDetected = false;
bool IndexerRunContinuously =false;
int indexerTask()
{
  bool ballAtTop = topLine.value(analogUnits::range10bit) < 700;
  bool ballAtMiddle = middleLine.value(analogUnits::range10bit) <715;
  bool ballAtBottom = bottomLine.value(analogUnits::range10bit) < 711;

  while (true)
  {
    if(IndexerStopWhenTopDetected) {
      std::cout <<topLine.value(analogUnits::range10bit) <<std::endl;
      if(topLine.value(analogUnits::range10bit) < 711) {
          Indexer.spin(fwd,0,volt);
          
        }
        else {
          Indexer.spin(fwd,12,volt);
        }

    }
    if(IndexerStopWhenMiddleDetected) {
      if(middleLine.value(analogUnits::range10bit) <697) {
        LOG(" Middle Ball detected");
        Indexer.spin(fwd,0,volt);
        task::sleep(200);
        Goal1.atGoal = false;
      }
      else {
        Indexer.spin(fwd,7,volt);
      }

    }
    if(IndexerStopWhenBottomDetected) {
      if(bottomLine.value(analogUnits::range10bit) < 695) {
        LOG("ball at bottom");
        Indexer.spin(fwd,0,volt);

      }
      else {
        Indexer.spin(fwd,10,volt);
      } 
    }
    if(IndexerRunContinuously) {
      Indexer.spin(fwd,12,volt);
    }
    if(Goal1.atGoal) {
      IndexerStopWhenMiddleDetected = true;

    }


    task::sleep(5);
  }

}

void stopIndexerTask(task taskID) {
  taskID.suspend();
  Indexer.spin(fwd,0,volt);
}