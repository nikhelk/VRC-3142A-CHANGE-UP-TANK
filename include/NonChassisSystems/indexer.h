#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"
#include "Util/mathAndConstants.h"

using namespace vex;

namespace Rollers{

int indexerTask(void* toBeCastedBools);

void stopIndexerTask(task taskID);

enum IndexerVoltages {

    INDEXER_VOLTAGE = 12,
    INDEXER_STOP_VOLTAGE = 0,
    INDEXER_OUTY_VOLTAGE = 8

};

}
