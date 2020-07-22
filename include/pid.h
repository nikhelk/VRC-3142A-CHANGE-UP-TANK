#pragma once
#include "vex.h"
typedef struct _posPID {
double  kP;
double kI;
double kD;
double kBias;
double error;
double prevError;
int integral;
int derivative;

	//PID limits
int errorThreshold;
int integralLimit;
int upperBound;
int lowerBound;

	//Timestep
int dt;
double currentTime;
double prevTime;

	//Input
double targetPos;
double currentPos;
float *var;
	//Output
double outVal;
} pos_PID;

void pos_PID_InitController(pos_PID *pid,double kP, double kI, double kD, double kBias = 0.0, int errorThreshold = 0, int integralLimit = 1000000);


//void pos_PID_SetTargetPosition(posPID *pid, const double targetPos);

double pos_PID_CalculatePower(pos_PID *pid,double targetPos,double currentPos);

 struct pidTimer {
    int      close;
    int     notMoved;
};