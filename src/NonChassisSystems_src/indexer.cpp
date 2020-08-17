#include "NonChassisSystems/indexer.h"


int indexerTask()
{
  while (true)
  {
    Indexer.spin(fwd, 12, volt);
    task::sleep(5);
  }
}