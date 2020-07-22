#include "vex.h"

double drawDistanceElapsed;
long drawCurrentLeft,drawCurrentRight;
int successTask( void *arg ) {
    if( arg == NULL ) return 0;
    long drawEncoderLeft = leftFront.position(degrees);
    long drawEncoderRight = rightFront.position(degrees);
    graph *g = static_cast<graph *>(arg);
    int x = 180;
    while(1) {
    drawCurrentLeft = leftFront.position(degrees) - drawEncoderLeft;
    drawCurrentRight = rightFront.position(degrees) - drawEncoderRight;
    drawDistanceElapsed = (drawCurrentLeft + drawCurrentRight) / 2.0;
      if((drawDistanceElapsed/ factor) == desired/factor) {
      g->addPoint( 2, desired/factor );;
      if( x++ == 360 )
        x = 0;
      Brain.Screen.printAt(50,100,"%DONE");
      
    }
    this_thread::sleep_for(10);
    }
}

int goalTask( void *arg ) {
    if( arg == NULL ) return 0;
    long drawEncoderLeft = leftFront.position(degrees);
    long drawEncoderRight = rightFront.position(degrees);
    graph *g = static_cast<graph *>(arg);
    while(1) {
      drawCurrentLeft = leftFront.position(degrees) - drawEncoderLeft;
      drawCurrentRight = rightFront.position(degrees) - drawEncoderRight;
      drawDistanceElapsed = (drawCurrentLeft + drawCurrentRight) / 2.0;
      g->addPoint( 0, desired/(factor) );
      Brain.Screen.printAt(50,100,"%f",drawDistanceElapsed/encoderToInch);
      this_thread::sleep_for(10);
    }
}

int currentTask( void *arg ) {
    if( arg == NULL ) return 0;
    long drawEncoderLeft = leftFront.position(degrees);
    long drawEncoderRight = rightFront.position(degrees);
    graph *g = static_cast<graph *>(arg);

    int y = 0;
    int inc = 1;
    while(1) {
      drawCurrentLeft = leftFront.position(degrees) - drawEncoderLeft;
    drawCurrentRight = rightFront.position(degrees) - drawEncoderRight;
    drawDistanceElapsed = (drawCurrentLeft + drawCurrentRight) / 2.0;
     g->addPoint( 1, (drawDistanceElapsed)/(encoderToInch * factor));

      if( abs(y+=inc) == 80 ) {
        inc = -inc;
      }

      this_thread::sleep_for(10);
    }
    //bruh bru1
}