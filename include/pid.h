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

 struct pidTimer {
    int      close;
    int     notMoved;
};