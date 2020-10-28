/*



#include "vex.h"
#define SAMPLE_COUNT  1000.0
#define CHASSIS_BASE_IN 14.0


void setDrive(double leftVelocity, double rightVelocity);
using namespace vex;
typedef struct _spconfig {
  double t;
  double x;
  double y;
  double dx;
  double dy;
  double curvature;
  double lengthProgress;

} splineConfig;
typedef struct mp {
double accelTime;
double decelTime;
double distanceAccel;
double distanceCoast;
double coastTime;
double distanceDecel;
double fullSpeedDist;
double maxVel;
double maxAcc;
double totalTime;
double test;
double distance;
} mp;
mp trapezoid;
void generateTrapMP(const double maxVel, const double maxAcc,const double distance) {
  trapezoid.maxVel = maxVel;
  trapezoid.maxAcc = maxAcc;
  trapezoid.distance = distance;
  trapezoid.accelTime = trapezoid.maxVel/trapezoid.maxAcc;
  trapezoid.decelTime = trapezoid.maxVel/trapezoid.maxAcc;
  trapezoid.distanceAccel =.5*trapezoid.accelTime*trapezoid.maxVel;
  trapezoid.distanceCoast = (trapezoid.distance-(2*trapezoid.distanceAccel));
  trapezoid.coastTime =trapezoid.distanceCoast/maxVel;
  if (trapezoid.distanceCoast < 0) {
    trapezoid.accelTime = sqrt(trapezoid.distance / trapezoid.maxAcc);
    trapezoid.distanceCoast = 0;
  }
  trapezoid.distanceDecel = .5*trapezoid.decelTime*maxVel;
  trapezoid.totalTime = trapezoid.accelTime + trapezoid.coastTime + trapezoid.decelTime;
  trapezoid.test = 10;
}


class MotionProfile {
  private:
    double accelTime;
    double decelTime;
    double distanceAccel;
    double distanceCoast;
    double coastTime;
    double distanceDecel;
    double fullSpeedDist;
    double maxVel;
    double maxAcc;
    double totalTime;
    double test;
    double distance;
  public:
    MotionProfile(double maxVel, double maxAcc, double distance);
    double calculateMpVelocity(const double t);
    std::string getMpStatus(const double t);

};

MotionProfile::MotionProfile(double maxVel, double maxAcc, double distance) {
      this->maxAcc = maxAcc;
      this->maxVel = maxVel;
      this->distance = distance;
      this->accelTime =this->maxVel/this->maxAcc;
      this->decelTime = this->maxVel/this->maxAcc;
      this->distanceAccel =.5*this->accelTime*this->maxVel;
      this->distanceCoast = (this->distance-(2*this->distanceAccel));
      this->coastTime =this->distanceCoast/maxVel;
      if (this->distanceCoast < 0) {
        this->accelTime = sqrt(this->distance / this->maxAcc);
        this->distanceCoast = 0;
      }
      this->distanceDecel = .5*this->decelTime*this->maxVel;
      this->totalTime = this->accelTime + this->coastTime + this->decelTime;
    }
double MotionProfile::calculateMpVelocity(const double t) {
  double accelVelocity;
  if(t<this->accelTime) {
    //accelVelocity =(t*trapezoid.distanceAccel)/trapezoid.accelTime;
    accelVelocity =(t*(this->maxAcc));
    return(accelVelocity);}
  else if(t>this->accelTime && t<(this->accelTime+this->coastTime))
    return(this->maxVel);
  else if(t>this->accelTime+this->coastTime && t<this->totalTime){
    //return(((trapezoid.totalTime-t)*trapezoid.distanceDecel)/trapezoid.decelTime);
    return(((this->totalTime-t)*(this->maxAcc)));
  }
  return 0;
}



std::string MotionProfile::getMpStatus(const double t) {
  if(t<this->accelTime)
    return("accelerating");
  else if(t>this->accelTime && t<this->accelTime+this->coastTime)
    return("coasting");
  else if(t>this->accelTime+this->coastTime && t<this->totalTime)
    return("decelerating");
  return("done");
}





typed3f struct _waypoint {
  double x;
  double y;
  double angle;
} Waypoint;

typedef struct _coefficients {
  double a;
  double b;
  double c;
  double d;
} CoefficientList;

typedef struct _controlPoints {
  double initial;
  double final;
  double initialVel;
  double finalVel;
} controlPoints;
typedef struct _trajectory {
  double time;
  double velocity;
  double acceleration;
  double angularVelocity;
} trajectory;
typedef struct _wheelSpeeds {
  double left;
  double right;
} wheelSpeeds;

//list of waypoints in form of  x (inches),y (inches), exit angle (radians)
Waypoint WaypointList[] ={ {0,0,0} , {25,0,M_PI/2}   }
int waypointSize = sizeof(WaypointList)/sizeof(Waypoint);
//std::vector<splineConfig> splinePoints;

//finds initial x, y, dx, dy for each point
std::vector<controlPoints> setControlPoints(int index) {
  std::vector<controlPoints> controlList;
  controlList.push_back({WaypointList[index].x, WaypointList[index+1].x,cos(WaypointList[index].angle),cos(WaypointList[index+1].angle)});
  controlList.push_back({WaypointList[index].y, WaypointList[index+1].y,sin(WaypointList[index].angle),sin(WaypointList[index+1].angle)});
  return(controlList);
}

//gets the coeffiencts for the cubic polynomial
std::vector<CoefficientList> getCoefficients(std::vector<controlPoints> controlList) {
  std::vector<CoefficientList> cubicCoeffs(2); //length is two as one contains x polynomaial coefficents and the other contains the y coefficents
  for(int i = 0; i < controlList.size(); i++) {
  cubicCoeffs[i].d = controlList[i].initial;
  cubicCoeffs[i].c= controlList[i].initialVel;
  cubicCoeffs[i].a = 2* controlList[i].initial - 2* controlList[i].final + controlList[i].initialVel + controlList[i].finalVel;
  cubicCoeffs[i].b= -3*controlList[i].initial + 3* controlList[i].final - 2* controlList[i].initialVel - controlList[i].finalVel;

  }
  return(cubicCoeffs);
}

//finds the x, y, dx, dy at each "t"
splineConfig getVectors(double t,std::vector<CoefficientList> coeffs) {
  splineConfig sampleConfig;
  sampleConfig.t = t;
  sampleConfig.x = coeffs[0].a*t*t*t + coeffs[0].b*t*t +coeffs[0].c *t + coeffs[0].d;//at^3 + bt^2 +ct + d
  sampleConfig.y = coeffs[1].a*t*t*t + coeffs[1].b*t*t +coeffs[1].c *t + coeffs[1].d;//
  sampleConfig.dx = 3*coeffs[0].a*t*t + 2*coeffs[0].b*t +coeffs[0].c;//derivative of above (3at^2 + 2bt +c)
  sampleConfig.dy = 3*coeffs[1].a*t*t + 2*coeffs[1].b*t +coeffs[1].c;
  double ddx =  6*coeffs[0].a*t + 2*coeffs[0].b; //second derivative 6at +2b
  double ddy = 6*coeffs[1].a*t + 2*coeffs[1].b;
  double dx_2 =  sampleConfig.dx * sampleConfig.dx;
  double dy_2 = sampleConfig.dy * sampleConfig.dy;
  sampleConfig.curvature = std::abs(sampleConfig.dx * ddy - ddx * sampleConfig.dy) /  ((dx_2*dy_2) * sqrt(dx_2 + dy_2)); //formula for curvature
  if(std::isnan(sampleConfig.curvature)) { //checking if curvature is undefined i.e. robot is moving straight
    sampleConfig.curvature = 0;

  }
  return(sampleConfig);
};
std::vector<splineConfig> splinePoints;
bool doneParametizing = false;
void parametrize(std::vector<CoefficientList> coeffs) {

  std::vector<splineConfig> distanceParametrized;
  double tStep = 1/SAMPLE_COUNT;
  double arcLength = 0;
  splinePoints.push_back({0,WaypointList[0].x,WaypointList[0].y,cos(WaypointList[0].angle),sin(WaypointList[0].angle),0,0});
  for(int i = 1; i<SAMPLE_COUNT; i++) {
    splineConfig dataPoint = getVectors(i/SAMPLE_COUNT,coeffs);
    arcLength +=sqrt(dataPoint.dx*dataPoint.dx + dataPoint.dy*dataPoint.dy)/SAMPLE_COUNT;
    //std::cout << arcLength << std::endl;
    dataPoint.lengthProgress = arcLength;
    splinePoints.push_back(dataPoint);
  }
  double endpoint = splinePoints[SAMPLE_COUNT-1].lengthProgress;
  double dsMax =1;
  int skipper = 0;
 // task::sleep(100);
 std::cout << "done initializing array!!!";
  for(int i = 0; i <SAMPLE_COUNT;i = i + 1) {
  //double ds = splinePoints[i+1].lengthProgress-splinePoints[i].lengthProgress;
  splineConfig upper;
  splineConfig lower;

  upper = splinePoints[i+1];

  lower = splinePoints[i];
  double ds = upper.lengthProgress-lower.lengthProgress;
  bool isLower = ds < dsMax;
  //std::cout << isLower<< " " <<i << " " << skipper << std::endl;
  task::sleep(10);
  if (ds < dsMax) {
    splinePoints.erase(splinePoints.begin() +i +1);
    i--;

  }
        skipper +=1;
    if(skipper ==SAMPLE_COUNT-1) {
        break;
    }

  }
  std::cout <<( getVectors(1,coeffs).lengthProgress)<<std::endl;;
  splinePoints.push_back(getVectors(1,coeffs));
  splinePoints.push_back(getVectors(1,coeffs));
  doneParametizing = true;
}
std::vector<splineConfig> spline2;

std::vector<trajectory> hi(const double maxVel, const double maxAcc) {
  generateTrapMP( maxVel,  maxAcc,splinePoints[SAMPLE_COUNT-1].lengthProgress);
  std::vector<trajectory> trapeziodal;
  trapeziodal.push_back({0,0,0,0});
  double totalT = 0;
  for (int i = 0; i< splinePoints.size()-1; i++) {
    double ds = splinePoints[i+1].lengthProgress;
    double dt = sqrt((2*ds)/maxAcc);
   // std::cout << ds << " " << calculateMpVelocity(dt)<< " " <<getMpStatus(dt) <<std::endl;
    trapeziodal.push_back({dt,calculateMpVelocity(dt),maxAcc,calculateMpVelocity(dt)*splinePoints[i+1].curvature});
    //std::cout <<"hi"<<std::endl;
    task::sleep(10);
  }
  return(trapeziodal);
}
std::vector<wheelSpeeds> setWheelSpeeds(std::vector<trajectory> traj) {
  std::vector<wheelSpeeds> diffDriveSpeeds;
  for(int i = 0; i< traj.size()-1;i++) {
    double left = traj[i].velocity - (CHASSIS_BASE_IN / 2)
      * traj[i].angularVelocity;
    double right = traj[i].velocity + (CHASSIS_BASE_IN / 2)
      * traj[i].angularVelocity;
    diffDriveSpeeds.push_back({left,right});
  }
  return(diffDriveSpeeds);
}

int getTaskMakingStatus() {
  while(!doneParametizing) {
     Brain.Screen.printAt(100,150, "Parametrizing...");
    //Brain.Screen.render();
  }
    Brain.Screen.printAt(300,150, "DONE");
    return(-1);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
 std::vector<controlPoints> controlList;
  task status(getTaskMakingStatus);
  std::vector<controlPoints> control = setControlPoints(0);
  std::cout << "DONE" << std::endl;
  std::vector<CoefficientList> coeffs = getCoefficients(control);;
  std::cout << "DONE" << std::endl;
   parametrize(coeffs);
  std::cout << "DONE" << std::endl;
  Brain.Screen.printAt(50,50,"%d",Brain.Timer.time());
  //std::vector<splineConfig> stuff = distanceParametrize(coeffs,nonDistancedParametrize);
  for(int i =0; i < splinePoints.size(); i ++) {
    spline2.push_back(splinePoints[i]);

    task::sleep(10);
  }
 // parametrize(coeffs);
 // std::vector<trajectory> outy =  hi(42,21);
 // std::vector<wheelSpeeds> driveBotSpeeds = setWheelSpeeds(outy);
  //for(int i  =0; i <999; i++) {

   // std::cout << driveBotSpeeds[i].left << " " <<driveBotSpeeds[i].right << std::endl;
 //}
double time = Brain.Timer.time(sec);
double currentTime;
    int i =0;
   while( i <999) {
     setDrive(driveBotSpeeds[i].left*(60/(4*M_PI)),driveBotSpeeds[i].right*(60/(4*M_PI)));
     std::cout << driveBotSpeeds[i].left*(60/(4*M_PI)) << " " <<outy[i].velocity << std::endl;
     task::sleep(outy[i+1].time-outy[i].time);
     i ++;
}
setDrive(0, 0);



while(true) {


this_thread::sleep_for(10);
}

}

void setDrive(double leftVelocity, double rightVelocity) {
  leftFront.spin (fwd,leftVelocity, velocityUnits::rpm);
  leftBack.spin (fwd,leftVelocity, velocityUnits::rpm);
  rightFront.spin (fwd,rightVelocity, velocityUnits::rpm);
  rightBack.spin (fwd,rightVelocity, velocityUnits::rpm);
}


*/