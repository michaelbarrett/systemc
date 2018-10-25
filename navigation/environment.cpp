//environment.cpp
#include "environment.h"

const double DELTA_X = 0.1;
const double DELTA_Y = 0;

void environment :: prc() {
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
  if (distance(robotp, ))

  //part 4: for each robot, compare the distance from obstacles
  //- if the robot is close to the obstacle, stop the robot, send robot the status
  //and the robot sends the status to the server - "STOPPED"
  //- if the stopped robot is clear from obstacles, resume the robot, send robot the
  //status and the robot sends the status to the server - "MOVING"
}
