//environment.cpp
#include "environment.h"
#include "server.h"

const double DELTA_X = 0.1;
const double DELTA_Y = 0;
const int NUM_ROBOTS = 4;
const int NUM_HUMANS = 6;
const int NUM_ROWS = 3;

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

int environment:: myGridIndex(int robot_index) {
  int i = 0;
  double myx = robotx[robot_index];
  double myy = roboty[robot_index];
  //for each element in grid variable, {0: INDEX, 1: X1, 2: Y1, 3: X2, 4: Y2}
  for (i=0;i<sizeof(grid);i++) {
    int x1 = grid[i][1];
    int y1 = grid[i][2];
    int x2 = grid[i][3];
    int y2 = grid[i][4];
    if (myx < x2 && myx > x1 && myy < y2 && myy > y1) {
      return grid[i][0]; //return this grid index
    }
  }
  cout << "myGridIndex ERROR: INVALID GRID FOR ROBOT INDEX" << robot_index << endl;
  return -1;
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
    if (my_message != 2) {
      robotx += DELTA_X;
      roboty += DELTA_Y;
      cout << "robot x,y is: " << robotx << ", " << roboty << " and ";
    } else { cout << "robot is stopped by human." << " and "; }
     
    //part 2: each cycle, each obstacle updates its position
    humanx -= DELTA_X;
    humany -= DELTA_Y;
    cout << "human x,y is: " << humanx << ", " << humany << endl;
    cout << "message is: " << my_message << endl;
    
    if (my_message != 0) {
      my_message = 0;
    }

    //part 3: for each robot, compare the distance from the grid bounary.
    //if close to boundary, send signal to robot, then robot sends signal to server
    //we are checking with right boundary for now PHASE 2: check with all boundaries
    /*if (robotx == 1.9 || robotx == 3.9 || robotx == 5.9 || robotx == 7.9 || robotx == 9.9) {*/
    if ((robotx < 1.91 && robotx > 1.89) ||
	(robotx < 3.91 && robotx > 3.89) ||
	(robotx < 5.91 && robotx > 5.89) ||
	(robotx < 7.91 && robotx > 7.89) ||
	(robotx < 9.91 && robotx > 9.89) ) {
      //PHASE 2: actually check for robot
      //send signal "crossing" to robot->server
      cout << "sending message CROSSING to server" << endl;
      message.write(1);
      my_message = 1;
      server::message_from_env(1);
      cout << "sent message CROSSING" << message << endl;
      //      message.write(0);
    }

    //part 4: for each robot, compare the distance from obstacles
    //- if the robot is close to the obstacle, stop the robot, send robot the status
    //and the robot sends the status to the server - "STOPPED"
    //- if the stopped robot is clear from obstacles, resume the robot, send robot
    //status and the robot sends the status to the server - "MOVING"
    if (distance(robotx, roboty, humanx, humany) < 3) {
      cout << "stopped bc of human" << endl;
      message.write(2);
      my_message = 2;
      //wait();
      //message.write(0);
    }

    if (robotx > 4.3) {
      //wait();
    }
    cout << "get ready" << endl;
    wait();
    cout << "hi" << endl;
  }
}
