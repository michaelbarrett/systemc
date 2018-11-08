//environment.cpp
#include "environment.h"
#include "server.h"

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2.0));
}

double get_center_x(double x1, double y1, double x2, double y2) {
  return ((x1 + x2) / 2.0);
}

double get_center_y(double x1, double y1, double x2, double y2) {
  return ((y1 + y2) / 2.0);
}

double distance(int x1, int y1, int x2, int y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2.0));
}

double get_center_x(int x1, int y1, int x2, int y2) {
  return ((x1 + x2) / 2.0);
}

double get_center_y(int x1, int y1, int x2, int y2) {
  return ((y1 + y2) / 2.0);
}

//0 = Nothing, 1 = Acknowledged (Ack)
//int environment :: receive_message(int m) {
//  
//}

int environment :: get_x_center_of_grid(int grid_index) {
  double cx;
  int robot_grid_list[60];
  for (int i = 0; i < sizeof(robot_grid_list); i++) {
    robot_grid_list[i] = grid[robot_index-1][i];
  }
  cx = get_center_x(robot_grid_list[1], robot_grid_list[2], robot_grid_list[3], robot_grid_list[4]);
}

int environment :: get_y_center_of_grid(int grid_index) {
  double cy;
  int robot_grid_list[60];
  for (int i = 0; i < sizeof(robot_grid_list); i++) {
    robot_grid_list[i] = grid[robot_index-1][i];
  }
  cy = get_center_y(robot_grid_list[1], robot_grid_list[2], robot_grid_list[3], robot_grid_list[4]);
}

int environment :: my_grid_index(int robot_index) {
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
  cout << "my_grid_index ERROR: INVALID GRID FOR ROBOT INDEX" << robot_index << endl;
  return -1;
}

void environment :: prc() {
  //initialize robot positions
  server::set_current_grid_robot(0, 1);
  server::set_current_grid_robot(1, 10);
  cout << "Robot 0 grid index is " << server::get_current_grid_robot(0) << endl;
  cout << "Robot 1 grid index is " << server::get_current_grid_robot(1) << endl;

  while(1) {
    //current grid is found based on current location of all robots.

    //and next grid is moved towards.
    //Q: What is this robot? What is the next grid for this robot?

    //for each robot:
    //1. get the current grid and the next grid
    //2. update robot position
    for (int robot_index = 0; i<NUM_ROBOTS; robot_index++) {
      int current_grid, next_grid;
      current_grid = server::get_current_grid_robot(robot_index);
      next_grid = server::get_next_grid_robot(robot_index);
      //move by speed towards next grid in the path
      //do we move up, down, left, or right?
      //get the X and Y of the next grid. Compare it to our X and Y.
      //Then move towards it.
      double myx = robotx[robot_index];
      double myy = roboty[robot_index];
      //we have our x, our y, our current grid, and our next grid.
      //we need the desired x, desired y.
      //for this we need grid index ----> x and y
      double desiredx = get_center_x_of_grid[next_grid];
      double desiredy = get_center_y_of_grid[next_grid];
    }
    
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
      server::receive_message(1);
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

