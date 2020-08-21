#pragma once


struct PDcontroller
{
  double kP;
  double kD;
};

class posPID
{
private:
  double m_kP;
  double m_kD;

  double m_error;
  double m_prevError;
  double m_proportional;
  double m_derivative;

  static const int m_upperBound = 11; //max voltage
  static const int m_lowerBound = -11; //min voltage
  double m_power;

public:


  /**
   * default posPID constructor for values inputted in the FourMotorDrive constructor
   */

  posPID();

  /**
   * sets the PD values for custom PIDs in FourMotorDrive constructor
   * @param kP desired kP value
   * @param kD desired kD value
   */
  
  void setPD(double kP, double kD);
  
  
  /**
   * Creates a PD controller for drivetrain
   * @param kP value
   * @param kD value
   */

  posPID(double kP, double kD);



/**
   * Calculates power of PD drive controller
   * @param targetPos  desired position of robot
   * @param currentPos current position of robot
   * @return output power of controller
   */

  double calculatePower(double targetPos, double currentPos);

  /**
   * gets the error of the PD controller
   * @return error of controller
   */

  double getError() { return (m_error); }

  //gets kP value of controller
  double getKp() {return (m_kP);}

  //gets kD value of controller 
  double getKd() {return(m_kD);}

  /**
   * gets the power of the PD controller
   * @return error of controller
   */
  double getPower() { return (m_power); }
};


/**
 * struct pidTimer
 * timers for pid timeout
 */

struct pidTimer 
{
  int close; //if robot is close to target
  int notMoved; //if robot has not moved
};
