#include "NonChassisSystems\indexer.h"
#include "vex.h"

int indexerTask()
{
  while (true)
  {
    Indexer.spin(fwd, 12, volt);
    task::sleep(5);
  }
}