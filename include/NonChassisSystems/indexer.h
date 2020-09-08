#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"


using namespace vex;

namespace Rollers{

int indexerTask();

void stopIndexerTask(task taskID);

extern bool IndexerStopWhenTopDetected;

extern bool IndexerStopWhenMiddleDetected;

extern bool IndexerStopWhenBottomDetected;

extern bool IndexerRunContinuously;

enum IndexerVoltages {

    INDEXER_VOLTAGE = 12,
    INDEXER_STOP_VOLTAGE = 0,
    INDEXER_OUTY_VOLTAGE = 8

};

}
