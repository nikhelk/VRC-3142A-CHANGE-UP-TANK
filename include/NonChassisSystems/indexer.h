#pragma once
#include "Config/chassis-config.h"
#include "Config/other-config.h"
#include "Impl/auto_skills.h"
#include "Util/vex.h"

#include "Util/mathAndConstants.h"

using namespace vex;

namespace Rollers{

int indexerTask();


/// when we set this bool to true, then the indexer stops when the top line sensor detects a ball
extern bool IndexerStopWhenTopDetected;

/// when we set this bool to true, then the indexer stops when the middle line sensor detects a ball
extern bool IndexerStopWhenMiddleDetected;

/// when we set this bool to true, then the indexer runs at full speed
extern bool IndexerRunContinuously;

/// when we set this bool to true, then the indexer stops
extern bool IndexerStop;

// different voltages depending on what we are doing (admittedly, it was probably not the best idea to use an enum)
enum IndexerVoltages {

    INDEXER_VOLTAGE = 12,
    INDEXER_STOP_VOLTAGE = 0,
    INDEXER_OUTY_VOLTAGE = 8 //less than full 12 volts becuase it was overshooting the line sensor
};
}