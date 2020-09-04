#include "NonChassisSystems/indexer.h"
#include "NonChassisSystems/flywheel.h"
#include <iostream>


bool IndexerStopWhenTopDetected = false;
bool IndexerStopWhenMiddleDetected = false;
bool IndexerStopWhenBottomDetected = false;
bool IndexerRunContinuously =false;
int indexerTask()
{

  while (true)
  {

    if(IndexerStopWhenMiddleDetected) {
      if(middleLine.value(analogUnits::range10bit) <697) {
        LOG(" Middle Ball detected");
        Indexer.spin(fwd,0,volt);       
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

    if(atGoal) {

      IndexerRunContinuously = false;

      IndexerStopWhenBottomDetected = false;

      if(!scored) { // index to the middle while flywheel is scoring
        IndexerStopWhenMiddleDetected = true;
      }
      else { //run outy
        IndexerStopWhenMiddleDetected = false;
        Indexer.spin(fwd, 600*.5, velocityUnits::rpm);

      }

    }


    task::sleep(5);
  }

}

void stopIndexerTask(task taskID) {
  taskID.suspend();
  Indexer.spin(fwd,0,volt);
}