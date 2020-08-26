#include "NonChassisSystems/indexer.h"
#include <iostream>


bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected = false;
bool IndexerStopWhenBottomDetected = false;
bool IndexerRunContinuously =false;
int indexerTask()
{
  bool ballAtTop = topLine.value(analogUnits::range10bit) < 705;
  bool ballAtMiddle = middleLine.value(analogUnits::range10bit) <715;
  bool ballAtBottom = bottomLine.value(analogUnits::range10bit) < 705;

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
      LOG( middleLine.value(analogUnits::range10bit));
      if(middleLine.value(analogUnits::range10bit) <710) {
        LOG("Ball detected");
        Indexer.spin(fwd,0,volt);
      }
      else if (ballAtMiddle && ballAtTop) {
        Indexer.spin(fwd,0,volt);
      }
      else {
        Indexer.spin(fwd,7,volt);
      }

    }
    if(IndexerStopWhenBottomDetected) {
      if(ballAtBottom) {
        Indexer.spin(fwd,0,volt);
      }
      if(ballAtBottom && ballAtMiddle) {
        Indexer.spin(fwd,0,volt);
      }
      if(ballAtBottom && ballAtMiddle && ballAtTop) {
        Indexer.spin(fwd,0,volt);
      }
      else {
        Indexer.spin(fwd,12,volt);
      } 
    }
    if(IndexerRunContinuously) {
      Indexer.spin(fwd,12,volt);
    }


    task::sleep(5);
  }

}

void stopIndexerTask(task taskID) {
  taskID.suspend();
  Indexer.spin(fwd,0,volt);
}