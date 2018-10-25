//environment.cpp
#include "environment.h"

const double DELTA_X = 0.1;
const double DELTA_Y = 0;

void environment :: prc() {
  while(1) {
    //four loops
    //part 1: each cycle, each robot updates its position
    //> move delta x/y towards next grid in the path
    robotp.x += DELTA_X;
    robotp.y += DELTA_Y;

    //part 2: each cycle, each obstacle updates its position
    humanp.x -= DELTA_X;
    humanp.y -= DELTA_Y;

    //part 3: for each robot, compare the distance from the grid bounary.
    //if close to boundary, send signal to robot, then robot sends signal to server
    //we are checking with right boundary for now PHASE 2: check with all boundaries
    if (distance(robotp, new Point(grid[currGrid].topRight.x, 1)) = 0.5) {
      //PHASE 2: actually check for robot
      //send signal "crossing" to robot->server
      message.write(1);
    }

    //part 4: for each robot, compare the distance from obstacles
    //- if the robot is close to the obstacle, stop the robot, send robot the status
    //and the robot sends the status to the server - "STOPPED"
    //- if the stopped robot is clear from obstacles, resume the robot, send robot the
    //status and the robot sends the status to the server - "MOVING"
  }
}
