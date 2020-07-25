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

    /**
    * default posPID constructor for values inputted in the FourMotorDrive constructor
    */
    posPID();

    /**
    * Creates a PD controller for drivetrain
    * @param kP value
    * @param kD value
    */

    posPID(double kP, double kD);

    /**
    * Calculates power of PD drive controller definied in FourMotorDrive
    * @param PD controller
    * @param desired position of robot
    * @param current position of robot
    * @return output power of controller
    */


    double calculatePower(posPID *pid, double targetPos,double currentPos);


    /**
    * Calculates power of PD drive controller definied in FourMotorDrive
    * @param desired position of robot
    * @param current position of robot
    * @return output power of controller
    */


    double calculatePower( double targetPos,double currentPos);

    /**
    * gets the error of the PD controller
    * @return error of controller
    */
    
    double getError() {return(m_error);}

    /**
    * gets the power of the PD controller
    * @return error of controller
    */
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