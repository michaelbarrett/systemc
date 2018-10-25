//environment.cpp
#include "environment.h"

const double DELTA_X = 0.1;
const double DELTA_Y = 0;

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void environment :: prc() {
  while(1) {
    //current grid is found based on your current location and next grid is
    //moved towards.
    int currentGrid = 0;
    int nextGrid = 1;
    if (robotx > 0 && robotx <= 2) currentGrid = 0;
    else if (robotx > 2 && robotx <= 4) currentGrid = 1;
    else if (robotx > 4 && robotx <= 6) currentGrid = 2;
    else if (robotx > 6 && robotx <= 8) currentGrid = 3;
    else if (robotx > 8 && robotx <= 10) currentGrid = 4;
    
    //four loops
    //part 1: each cycle, each robot updates its position
    //> move delta x/y towards next grid in the path
    //compute a path based on your current location
    robotx += DELTA_X;
    roboty += DELTA_Y;
    cout << "test" << endl;

    //part 2: each cycle, each obstacle updates its position
    humanx -= DELTA_X;
    humany -= DELTA_Y;

    //part 3: for each robot, compare the distance from the grid bounary.
    //if close to boundary, send signal to robot, then robot sends signal to server
    //we are checking with right boundary for now PHASE 2: check with all boundaries
    if (robotx == 1.9 || robotx == 3.9 || robotx == 5.9 || robotx == 7.9 || robotx == 9.9) {
      //PHASE 2: actually check for robot
      //send signal "crossing" to robot->server
      message.write(1);
      wait();
      message.write(0);
    }

    //part 4: for each robot, compare the distance from obstacles
    //- if the robot is close to the obstacle, stop the robot, send robot the status
    //and the robot sends the status to the server - "STOPPED"
    //- if the stopped robot is clear from obstacles, resume the robot, send robot the
    //status and the robot sends the status to the server - "MOVING"
    if (distance(robotx, roboty, humanx, humany) < 3) {
      message.write(2);
      wait();
      message.write(0);
    }
  }
}
