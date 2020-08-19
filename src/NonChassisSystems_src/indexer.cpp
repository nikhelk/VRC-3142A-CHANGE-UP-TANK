#include "NonChassisSystems/indexer.h"
#include <iostream>


bool stopWhenTopDetected = false;
int indexerTask()
{
  while (true)
  {
    Indexer.spin(fwd, 12, volt);
    if(stopWhenTopDetected)
      if(chassis.leftFront.position(degrees) >= 360)
        Indexer.spin(fwd, 0, volt);
    std::cout << chassis.leftFront.position(degrees) << std::endl;
    task::sleep(5);
  }
  Indexer.spin(fwd, 0, volt);
  std::cout <<"DONE" <<std::endl;
}

void stopIndexerTask(task taskID) {
  taskID.suspend();
  Indexer.spin(fwd,0,volt);
}