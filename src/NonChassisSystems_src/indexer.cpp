#include "NonChassisSystems/indexer.h"
#include <iostream>


bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected = false;
bool IndexerStopWhenBottomDetected = false;
int indexerTask()
{
  bool ballAtTop = topLine.value(analogUnits::range10bit) < 705;
  bool ballAtMiddle = middleLine.value(analogUnits::range10bit) <705;
  while (true)
  {
    if(IndexerStopWhenTopDetected) {
      std::cout <<topLine.value(analogUnits::range10bit) <<std::endl;
      if(ballAtTop) {
          Indexer.spin(fwd,0,volt);
          std::cout << "Top ball detected!" << std::endl;
        }
        else {
          Indexer.spin(fwd,12,volt);
        }

    }
    if(IndexerStopWhenMiddleDetected) {
      if(ballAtMiddle) {
        Indexer.spin(fwd,0,volt);
      }
      else if (ballAtTop) {
        Indexer.spin(fwd,0,volt);
      }
      else {
        Indexer.spin(fwd,12,volt);
      }

    }
    else {
      Indexer.spin(fwd,12,volt);
    }


    task::sleep(5);
  }

}

void stopIndexerTask(task taskID) {
  taskID.suspend();
  Indexer.spin(fwd,0,volt);
}