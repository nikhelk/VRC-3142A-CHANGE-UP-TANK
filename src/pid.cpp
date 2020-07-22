#include "vex.h"

void pos_PID_InitController(pos_PID *pid,double kP, double kI, double kD, double kBias, int errorThreshold, int integralLimit) 
{
  
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
	pid->kBias = kBias;

	pid->error = 0;
	pid->prevError = 0;
	pid->integral = 0;
	pid->derivative = 0;

	pid->errorThreshold = errorThreshold;
	pid->integralLimit = integralLimit;
	pid->upperBound = 100;
	pid->lowerBound = -12;

	pid->dt = 0;
	pid->prevTime = 0;



	pid->outVal = 0;
}

/*void pos_PID_SetTargetPosition(posPID *pid, const double targetPos)
{
	pid->targetPos = targetPos;

}*/

double pos_PID_CalculatePower(pos_PID *pid,double targetPos,double currentPos) {

	//Calculate timestep
  pid->dt = 10;
		//Scrap dt if zero
    pid->targetPos = targetPos;
    pid->currentPos = currentPos;
		pid->error = pid->targetPos - pid->currentPos;

	//If error is large enough, calculate integral and limit to avoid windup INTEGRAL STUFF
	/*if (abs(pid->error) > pid->errorThreshold && abs(pid->integral) < pid->integralLimit)
    {
      pid->integral = pid->integral + pid->error * pid->dt;

      //Reset integral if reached target or overshot
      if (pid->error == 0 || sgn(pid->error) != sgn(pid->prevError))
      {
        pid->integral = 0;
      }
      //Bound integral
      else
      {
        pid->integral = pid->integral * pid->kI > 127 ? 127.0 / pid->kI : pid->integral;
        pid->integral = pid->integral * pid->kI < -127 ? -127.0 / pid->kI : pid->integral;
      }
    }*/

	//Calculate derivative
	pid->derivative = (pid->error - pid->prevError);
	pid->prevError = pid->error;

	//Calculate output
	pid->outVal = (pid->error * pid->kP) + (pid->integral * pid->kI) + (pid->derivative * pid->kD) + pid->kBias;

	//Bound output
	if (pid->outVal > pid->upperBound)
	{
		pid->outVal = pid->upperBound;
	}
	else if (pid->outVal < pid->lowerBound)
	{
		pid->outVal = pid->lowerBound;
	}

	return pid->outVal;
}