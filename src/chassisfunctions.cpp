#include "vex.h"
using namespace std;

void driveStraight( const double distance) {
  bool atTarget = false; //are we at target no!
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;

  double unroundedTargetDistance = encoderToInch * distance;
  double targetDistance = truncf(unroundedTargetDistance * 10) / 10; //desired distance in encoder ticks rounded to tenths

  //pos_PID distancePID, anglePID;
  //pos_PID_InitController(&distancePID,.1 , 0 , .5); //inistiizng distance pid and values in orrder (kp,ki,kd)
  //pos_PID_SetTargetPosition(&distancePID, targetDistance);
  //pos_PID_InitController(&anglePID,.2, 0.0,0.0); //inistiizng "dampner" pid and values in orrder (kp,ki,kd)
  posPID distancePID(5,.5);
  posPID anglePID(.2,0);



  const long initialEncoderLeft = leftFront.position(degrees); //this is my way of resetting the encoder vals instead of setting them to 0
  const long initialEncoderRight = rightFront.position(degrees);



  const double atTargetDistance = 26/4; //if we are this close then we exit (this is in encoder ticks)
  pidTimer driveTimer;
  const double threshold = 2;//if we havent moved close then we exit (this is in encoder ticks)


  const int timeoutPeriod = 7000; //amount of time before exiting
  long currentLeft, currentRight;
  driveTimer.notMoved =0; //setting timers to 0
  driveTimer.close = 0;
  //double distancePower, anglePower;
  while(!atTarget) {

    currentLeft = leftFront.position(degrees) - initialEncoderLeft; //current left encoder
    currentRight = rightFront.position(degrees) -initialEncoderRight;

    distanceElapsed = (currentLeft + currentRight) / 2.0; //this is the amount we travelled (something the vex discord told me)
    angleChange = currentLeft-currentRight;

    //distancePower = pos_PID_CalculatePower(&distancePID,targetDistance,distanceElapsed); //function to calculate power where target is our target and distanceElapsed is current
    //anglePower = 0;
    //anglePower = pos_PID_CalculatePower(&anglePID,0,angleChange);//function to calculate angle change where target is our target and angleCange is current. in this case i have target set to 0 for straightdrive but it can be anything
    distancePID.calculatePower(targetDistance, distanceElapsed);
    anglePID.calculatePower(0, angleChange);

      setDrive(distancePID.getPower()+anglePID.getPower()
      ,distancePID.getPower()+anglePID.getPower()); // setting the drive and adding the correction pid
      std::cout << distancePID.getPower() << " " << anglePID.getPower() << " " <<distancePID.getError() <<std::endl;
      if (std::abs(targetDistance - distanceElapsed) <= atTargetDistance) //exit function
      {
        driveTimer.close += 10;
      }
      //Place mark if we haven't moved much
      else if (std::abs(distanceElapsed - lastDistance) <= threshold)
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceElapsed; //remember to store lastDistance for Kd calculation

      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod) // seeing if it exits
      {
        atTarget = true;
      } // debugging stuff
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0); //stopping bot
}


void turnToDegree(double angle)
{
	//Save left and right quad values instead of setting them to zero
	const long encoderLeft = leftFront.position(degrees);
  const long encoderRight = rightFront.position(degrees);

	//Total angle change since start
	double angleChange = 0, lastAngle = 0;

	//Conversion between encoder degrees and base_link degrees
	//const float conv = 12.88361;
  const double conv = 720/102.0;

	//Fix angle
	while(angle>180)
      angle-=360;
  while(angle<=-180)
      angle+=360;

	double targetAngle = angle * conv;



	//If angle PID controller is at target
	bool atTarget = false;

	//Angle that is "close enough" to target
	const int atTargetAngle = 10;

	//Threshold for not moving
	const int threshold = 2;

	//Timer for being at target
  pidTimer turnTimer;

	//Timeout period (ms)
	const int timeoutPeriod = 250;

	//Current left and right quad displacements
	long currentLeft, currentRight;

	//Distance and angle PID output
	double angleOutput;
  turnTimer.notMoved =0;
  turnTimer.close = 0;
	while (!atTarget)
	{
		//Calculate distance displacement
		currentLeft = leftFront.position(degrees) - encoderLeft;
		currentRight = rightFront.position(degrees) - encoderRight;

		angleChange = currentRight - currentLeft;
    angleOutput = chassis.turnPID.calculatePower(targetAngle, angleChange);

		//Set motors to angle PID output
		setDrive(angleOutput*-1,angleOutput);

		//Place mark if we're close enough to the target angle
		if (std::abs(targetAngle - angleChange) <= atTargetAngle)
		{
			turnTimer.close += 10;
		}
		//Place mark if we haven't moved much
		else if (std::abs(angleChange - lastAngle) <= threshold)
		{
			turnTimer.notMoved += 10;
		}
		else
		{
			turnTimer.close = 0;
      turnTimer.notMoved =0;
		}
    //cout << currentRight <<" " << currentLeft<< " " << " " << targetAngle/conv << " " <<angleChange/conv <<endl;
		lastAngle = angleChange;
		//If we've been close enough for long enough, we're there
		if (turnTimer.close >= timeoutPeriod||turnTimer.notMoved >=timeoutPeriod)
		{
			atTarget = true;
		}

		task::sleep(10);
	}
	setDrive(0,0);
}
double test2;
void moveToPoint(const double x, const double y, bool backwards, long offset)
{
	distanceAndAngle temp;
	computeDistanceAndAngleToPoint(x, y, &temp);
	if (backwards)
	{
		temp.theta += 180;
		temp.length *= -1;
	}

		turnToDegree(temp.theta);


		driveStraight(temp.length - offset);
}




void turnToAbsAngle(const double deg)
{
	long theta = 0;
	theta = positionArray[ODOM_THETA];

	turnToDegree(deg - theta);
}




void driveArcSortaWorks( const double angle,double radius) {
  bool atTarget = false;
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;
  double distance = toRadians(angle) * ( radius);
  double rRadius = radius + 7.0;
  double lRadius = radius - 7.0;
  double rDistance = rRadius * toRadians(angle);
  double lDistance = lRadius * toRadians(angle);
  double ratio = lDistance/rDistance;



  double unroundedTargetDistance = encoderToInch * distance;
  double targetDistance = truncf(unroundedTargetDistance * 10) / 10;




  const long encoderLeft = leftFront.position(degrees);
  const long encoderRight = rightFront.position(degrees);



  const double atTargetDistance = 26/4;
  pidTimer driveTimer;
  const double threshold = 2;

  double currentRatio = 0;
  const int timeoutPeriod = 250;
  long currentLeft, currentRight;
  driveTimer.notMoved =0;
  driveTimer.close = 0;
  double distancePower, anglePower,ratioPower;
  double curAngle = positionArray[ODOM_THETA];
  while(!atTarget) {
    currentLeft = leftFront.position(degrees) - encoderLeft;
    currentRight = rightFront.position(degrees) - encoderRight;
    if(currentRight ==0 || currentLeft ==0) {
      currentRatio =0;
    }
    else {
    currentRatio = (double)currentLeft/currentRight;
    }
   // std::cout << targetDistance << " " << 1/curvature << " " <<angleChange << " " << angle*(720/102.0)<<std::endl;
    distanceElapsed = (currentLeft + currentRight) / 2.0;
    angleChange = currentRight-currentLeft;
  //angleChange = positionArray[ODOM_THETA] - curAngle;
  distancePower = chassis.distancePID.calculatePower(targetDistance,distanceElapsed);

    std::cout << ratio << " " << currentRatio << " " <<360-poseTracker.inert.heading(degrees) <<std::endl;
      setDrive(ratio*(distancePower)+0,distancePower-0);
      if((360-poseTracker.inert.heading(degrees))-angle<2 &&(360-poseTracker.inert.heading(degrees))-angle>-2)
        atTarget = true;
      if (std::abs(targetDistance - distanceElapsed) <= atTargetDistance)
      {
        driveTimer.close += 10;
      }
      //Place mark if we haven't moved much
      else if (std::abs(distanceElapsed - lastDistance) <= threshold)
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceElapsed;

      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod)
      {
        atTarget = true;
      }
        Brain .Screen.printAt(100,150,"%f",leftFront.position(degrees));
        Brain .Screen.printAt(0,150,"timerClose: %.0f, timerNotMoved: %.0f",driveTimer.close,driveTimer.notMoved);
        Brain .Screen.printAt(0,200,"distanceElapsed: %.2f,Error %.2f  ",distanceElapsed,chassis.distancePID.KP);
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0);
}




void driveArc( const double angle,double radius) {
  bool atTarget = false;
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;
  double distance = angle*(M_PI/180) * (radius);
  double unroundedTargetDistance = encoderToInch * distance;
  double targetDistance = truncf(unroundedTargetDistance * 10) / 10;



  const long encoderLeft = leftFront.position(degrees);
  const long encoderRight = rightFront.position(degrees);



  const double atTargetDistance = 26/4;
  pidTimer driveTimer;
  const double threshold = 2;


  const int timeoutPeriod = 250;
  long currentLeft, currentRight;
  driveTimer.notMoved =0;
  driveTimer.close = 0;
  double distancePower, anglePower;
  double curAngle = positionArray[ODOM_THETA];
  while(!atTarget) {

    currentLeft = leftFront.position(degrees) - encoderLeft;
    currentRight = rightFront.position(degrees) - encoderRight;
   // std::cout << targetDistance << " " << 1/curvature << " " <<angleChange << " " << angle*(720/102.0)<<std::endl;
    distanceElapsed = (currentLeft + currentRight) / 2.0;
    angleChange = currentRight-currentLeft;
  //angleChange = positionArray[ODOM_THETA] - curAngle;

    //std::cout << distancePower + anglePower << " " << distancePower - anglePower << std::endl;
      setDrive(distancePower-anglePower,distancePower+anglePower);

      if (std::abs(targetDistance - distanceElapsed) <= atTargetDistance)
      {
        driveTimer.close += 10;
      }
      //Place mark if we haven't moved much
      else if (std::abs(distanceElapsed - lastDistance) <= threshold)
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceElapsed;

      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod)
      {
        atTarget = true;
      }
        Brain .Screen.printAt(100,150,"%f",leftFront.position(degrees));
        Brain .Screen.printAt(0,150,"timerClose: %.0f, timerNotMoved: %.0f",driveTimer.close,driveTimer.notMoved);
        Brain .Screen.printAt(0,200,"distanceElapsed: %.2f,Error %.2f  ",distanceElapsed);
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0);
}

void driveArc2( const double angle,double radius) {
  bool atTarget = false;
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;
  double distance = toRadians(angle) * ( radius);
  double rRadius = radius + 7.0;
  double lRadius = radius - 7.0;
  double rDistance = rRadius * toRadians(angle);
  double lDistance = lRadius * toRadians(angle);
  double ratio = lDistance/rDistance;



  double unroundedTargetDistance = encoderToInch * distance;
  double targetDistance = truncf(unroundedTargetDistance * 10) / 10;





  const long encoderLeft = leftFront.position(degrees);
  const long encoderRight = rightFront.position(degrees);



  const double atTargetDistance = 26/4;
  pidTimer driveTimer;
  const double threshold = 2;

  double currentRatio = 0;
  const int timeoutPeriod = 2000;
  long currentLeft, currentRight;
  driveTimer.notMoved =0;
  driveTimer.close = 0;
  double distancePower, anglePower,ratioPower;
  posPID arcPID(9,.3);
  double curAngle = positionArray[ODOM_THETA];
  while(!atTarget) {
    currentLeft = chassis.leftFront.position(degrees) - encoderLeft;
    currentRight = chassis.rightFront.position(degrees) - encoderRight;
    if(currentRight ==0 || currentLeft ==0) {
      currentRatio =0;
    }
    else {
    currentRatio = (double)currentLeft/currentRight;
    }
   // std::cout << targetDistance << " " << 1/curvature << " " <<angleChange << " " << angle*(720/102.0)<<std::endl;
    distanceElapsed = (currentLeft + currentRight) / 2.0;
    angleChange = currentRight-currentLeft;
  //angleChange = positionArray[ODOM_THETA] - curAngle;
  distancePower =  chassis.distancePID.calculatePower(targetDistance, distanceElapsed);
   // double realPower = distancePower/11;
    //anglePower = 0;

    std::cout << distancePower << " " << currentRatio << " " << ratio <<std::endl;
      setDrive(ratio*(distancePower)+ratioPower,distancePower-ratioPower);

      if (std::abs(targetDistance - distanceElapsed) <= atTargetDistance)
      {
        driveTimer.close += 10;
      }
      //Place mark if we haven't moved much
      else if (std::abs(distanceElapsed - lastDistance) <= threshold)
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceElapsed;

      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod)
      {
        atTarget = true;
      }
        Brain .Screen.printAt(100,150,"%f",leftFront.position(degrees));
        Brain .Screen.printAt(0,150,"timerClose: %.0f, timerNotMoved: %.0f",driveTimer.close,driveTimer.notMoved);
        Brain .Screen.printAt(0,200,"distanceElapsed: %.2f,Error %.2f  ",distanceElapsed,targetDistance);
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0);
}

void driveArc3( const double angle,double radius) {
  bool atTarget = false;
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;

  double rRadius = radius + 7.0;
  double lRadius = radius - 7.0;
  double rDistance = rRadius * toRadians(angle);
  double lDistance = lRadius * toRadians(angle);
  double ratio = lDistance/rDistance;
  double distance = (rDistance+lDistance)/2;



  double unroundedTargetDistance = encoderToInch * distance;
  double targetDistance = truncf(unroundedTargetDistance * 10) / 10;




  const long encoderLeft = leftFront.position(degrees);
  const long encoderRight = rightFront.position(degrees);



  const double atTargetDistance = 26/4;
  pidTimer driveTimer;
  const double threshold = 2;

  double currentRatio = 0;
  const int timeoutPeriod = 250;
  long currentLeft, currentRight;
  driveTimer.notMoved =0;
  driveTimer.close = 0;
  double distancePower, anglePower,ratioPower;
  double curAngle = positionArray[ODOM_THETA];
  while(!atTarget) {
    currentLeft = leftFront.position(degrees) - encoderLeft;
    currentRight = rightFront.position(degrees) - encoderRight;
    if(currentRight ==0 || currentLeft ==0) {
      currentRatio =0;
    }
    else {
    currentRatio = (double)currentLeft/currentRight;
    }
    std::cout << targetDistance << " " <<distanceElapsed<<std::endl;
    distanceElapsed = (currentLeft + currentRight) / 2.0;
    angleChange = currentRight-currentLeft;
  //angleChange = positionArray[ODOM_THETA] - curAngle;
    /*distancePower = pos_PID_CalculatePower(&distancePID,targetDistance,distanceElapsed);
    ratioPower =  pos_PID_CalculatePower(&ratioPID,ratio,currentRatio);
    double realPower = distancePower*2;
    //anglePower = 0;
    anglePower = pos_PID_CalculatePower(&anglePID,angle*(720/102.0),angleChange);*/
    //std::cout << ratio << " " << currentRatio << std::endl;
      //setDrive(ratio*(realPower)-ratioPower,realPower+ratioPower);

      if (std::abs(targetDistance - distanceElapsed) <= atTargetDistance)
      {
        driveTimer.close += 10;
      }
      //Place mark if we haven't moved much
      else if (std::abs(distanceElapsed - lastDistance) <= threshold)
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceElapsed;

      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod)
      {
        atTarget = true;
      }
        Brain .Screen.printAt(100,150,"%f",leftFront.position(degrees));
        Brain .Screen.printAt(0,150,"timerClose: %.0f, timerNotMoved: %.0f",driveTimer.close,driveTimer.notMoved);
       // Brain .Screen.printAt(0,200,"distanceElapsed: %.2f,Error %.2f  ",distanceElapsed,distancePID.currentPos);
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0);
}




void driveArc4( const double x,const double y,double angle) {
  posPID hi;
  
  bool atTarget = false;
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;
  distanceAndAngle start;
  computeDistanceAndAngleToPoint(x, y, &start);
  double distanceLeft = start.length;
  double unroundedTargetDistance = encoderToInch * distanceLeft;
  double targetDistance = truncf(unroundedTargetDistance * 10) / 10;




  const long encoderLeft = leftFront.position(degrees);
  const long encoderRight = rightFront.position(degrees);



  const double atTargetDistance = .3;
  pidTimer driveTimer;
  const double threshold = .3;


  double targetMinimize = 0;
  const int timeoutPeriod = 250;
  long currentLeft, currentRight;
  driveTimer.notMoved =0;
  driveTimer.close = 0;
  double distancePower, anglePower;
  double curAngle = positionArray[ODOM_THETA];
  while(!atTarget) {
    distanceAndAngle temp;
    computeDistanceAndAngleToPoint(x, y, &temp);
    distanceLeft = temp.length;
    currentLeft = leftFront.position(degrees) - encoderLeft;
    currentRight = rightFront.position(degrees) - encoderRight;
    std::cout << targetDistance << " " << distanceLeft << " " <<curAngle << " " << angle*(720/102.0)<<std::endl;
    distanceElapsed = (currentLeft + currentRight) / 2.0;
    angleChange = currentRight-currentLeft;
    curAngle = positionArray[ODOM_THETA];

    //std::cout << distancePower + anglePower << " " << distancePower - anglePower << std::endl;
      setDrive(-distancePower-anglePower,-distancePower+anglePower);

      if (std::abs(targetMinimize - distanceLeft) <= atTargetDistance)
      {
        driveTimer.close += 10;
      }
      //Place mark if we haven't moved much
      else if (std::abs(targetMinimize - lastDistance) <= threshold)
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceLeft;

      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod ||distanceLeft<atTargetDistance)
      {
        atTarget = true;
      }
        Brain .Screen.printAt(100,150,"%f",leftFront.position(degrees));
        Brain .Screen.printAt(0,150,"timerClose: %.0f, timerNotMoved: %.0f",driveTimer.close,driveTimer.notMoved);
        //Brain .Screen.printAt(0,200,"distanceElapsed: %.2f,Error %.2f  ",distanceElapsed,distancePID.currentPos);
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0);
}

void driveArc5(const double left, const double right) {
  bool atTarget = false;
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;

  
  const long desiredRatio = left/right;




  const long encoderLeft = leftFront.position(degrees);
  const long encoderRight = rightFront.position(degrees);


  long lastLeft,lastRight;
  const double atTargetDistance = 26/4;
  pidTimer driveTimer;
  const double threshold = 2;

  double currentRatio = 0;
  const int timeoutPeriod = 250;
  long currentLeft, currentRight;
  driveTimer.notMoved =0;
  driveTimer.close = 0;
  double leftPower, rightPower, ratioPower;
  double curAngle = positionArray[ODOM_THETA];
  while(!atTarget) {
    currentLeft = leftFront.position(degrees) - encoderLeft;
    currentRight = rightFront.position(degrees) - encoderRight;
    if(currentRight ==0 || currentLeft ==0) {
      currentRatio =0;
    }
    else {
    currentRatio = (double)currentLeft/currentRight;
    }
    distanceElapsed = (currentLeft + currentRight) / 2.0;
    angleChange = currentRight-currentLeft;
  //angleChange = positionArray[ODOM_THETA] - curAngle;
    
    //anglePower = 0;
    //std::cout << ratio << " " << currentRatio << std::endl;
      setDrive(leftPower+ratioPower,rightPower-ratioPower);

      if (std::abs(left - currentLeft) <= atTargetDistance||std::abs(right - currentRight) <= atTargetDistance)
      {
        driveTimer.close += 1010;
      }
      //Place mark if we haven't moved much
      else if (std::abs(currentLeft - lastLeft) <= threshold||(std::abs(currentRight - lastRight) <= threshold))
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(currentLeft - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceElapsed;
      lastLeft = currentLeft;
      lastRight = currentRight;
      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod)
      {
        atTarget = true;
      }
        Brain .Screen.printAt(100,150,"%f",leftFront.position(degrees));
        Brain .Screen.printAt(0,150,"timerClose: %.0f, timerNotMoved: %.0f",driveTimer.close,driveTimer.notMoved);
        //Brain .Screen.printAt(0,200,"distanceElapsed: %.2f,Error %.2f  ",distanceElapsed,distancePID.currentPos);
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0);
}


void moveToPointArc(const double x, const double y, const double theta) {
  distanceAndAngle temp2;
	computeDistanceAndAngleToPoint(x, y, &temp2);
  double radius = temp2.length/(2*sin(toRadians(theta/2)));
  driveArc2(theta, radius);


}

void driveStraightFeedforward(const double distance) {
  bool atTarget = false;
  double startTimeA = Brain.timer(vex::timeUnits::sec);
  double mpVel;
  generateTrapMP(42,260,distance);
  double distanceElapsed =0, angleChange = 0;
  double lastDistance =0;

  double unroundedTargetDistance = encoderToInch * distance;
  double targetDistance = truncf(unroundedTargetDistance * 10) / 10; //desired distance in encoder ticks rounded to tenths

  double currentTime;



  const long initialEncoderLeft = leftFront.position(degrees); //this is my way of resetting the encoder vals instead of setting them to 0
  const long initialEncoderRight = rightFront.position(degrees);



  const double atTargetDistance = 26/4; //if we are this close then we exit (this is in encoder ticks)
  pidTimer driveTimer;
  const double threshold = 0;//if we havent moved close then we exit (this is in encoder ticks)


  const int timeoutPeriod = 250; //amount of time before exiting
  long currentLeft, currentRight;
  driveTimer.notMoved =0; //setting timers to 0
  driveTimer.close = 0;
  double distancePower, anglePower;
  while(!atTarget) {

    currentLeft = leftFront.position(degrees) - initialEncoderLeft; //current left encoder
    currentRight = rightFront.position(degrees) -initialEncoderRight;

    distanceElapsed = (currentLeft + currentRight) / 2.0; //this is the amount we travelled (something the vex discord told me)
    angleChange = currentLeft-currentRight;
    currentTime = Brain.timer(vex::timeUnits::sec) - startTimeA;
    mpVel = calculateMpVelocity(currentTime)*60*(1/(4*M_PI));
    double ogVel = calculateMpVelocity(currentTime);
 

    std::string currentStatus = getMpStatus(currentTime);
    cout << mpVel << " " << distanceElapsed/26.3 << " " << currentStatus<<endl;
      setVelDrive(mpVel,mpVel); // setting the drive and adding the correction pid

      if (std::abs(targetDistance - distanceElapsed) <= atTargetDistance) //exit function
      {
        driveTimer.close += 10;
      }
      //Place mark if we haven't moved much
      else if (std::abs(distanceElapsed - lastDistance) <= threshold)
      {
        driveTimer.notMoved  +=10;
      }
      else
      {
        driveTimer.close=0;
        driveTimer.notMoved=0;
      }
      bool close = std::abs(targetDistance - distanceElapsed) <= atTargetDistance;
      bool stop = std::abs(distanceElapsed - lastDistance) <= threshold;
      bool pass = driveTimer.notMoved >=timeoutPeriod;
      bool pass2 = driveTimer.close >= timeoutPeriod;

      //printf("%.1f %ld %ld \n",angleChange,currentLeft,currentRight);
      lastDistance = distanceElapsed; //remember to store lastDistance for Kd calculation

      //If we've been close enough for long enough, we're there
      if (driveTimer.close >= timeoutPeriod||driveTimer.notMoved >=timeoutPeriod) // seeing if it exits
      {
        atTarget = true;
      } // debugging stuff
        Brain .Screen.printAt(100,150,"%f",leftFront.position(degrees));
        Brain .Screen.printAt(0,150,"timerClose: %.0f, timerNotMoved: %.0f",driveTimer.close,driveTimer.notMoved);
        //Brain .Screen.printAt(0,200,"distanceElapsed: %.2f,Error %.2f  ",distanceElapsed,distancePID.currentPos);
        task::sleep(10);
      }
      Brain.Screen.clearScreen();
    setDrive(0,0); //stopping bot
    
  
  
}

void setVelDrive(double leftVelocity, double rightVelocity) {
  leftFront.spin (fwd,leftVelocity, velocityUnits::rpm);
  leftBack.spin (fwd,leftVelocity, velocityUnits::rpm);
  rightFront.spin (fwd,rightVelocity, velocityUnits::rpm);
  rightBack.spin (fwd,rightVelocity, velocityUnits::rpm);
}

void setDrive(double leftVoltage,double rightVoltage) {
  leftFront.spin (fwd,leftVoltage, volt);
  leftBack.spin(fwd,leftVoltage,volt);
  rightFront.spin(fwd,rightVoltage,volt);
  rightBack.spin(fwd,rightVoltage,volt);
}


