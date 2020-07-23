#pragma once
#include "vex.h"

struct PDcontroller {
  double kP;
  double kD;
};

class posPID{
  private:
    double m_kP;
    double m_kD;

    double m_error;
    double m_prevError;
    double m_proportional;
    double m_derivative;

    static const int m_upperBound=10;
    static const int m_lowerBound = -10;
    double m_power;
    
  public:
    double KP;
    double KD;
    posPID();
    posPID(double kP, double kD);
    void calculatePower(posPID *pid, double targetPos,double currentPos);
    double getError() {return(m_error);}
    double getPower() {return(m_power);}


};
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
//static const int upperBound=10;
//static const int lowerBound = -10;
int upperBound=10;
int lowerBound = -10;
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