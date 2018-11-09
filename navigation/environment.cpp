//environment.cpp
//environment.cpp
#include "helper.h"
#include "environment.h"
#include "server.h"

//0 = Nothing, 1 = Acknowledged (Ack)
//int environment :: receive_message(int m) {
//  
//}

double environment :: get_x_center_of_grid(int grid_index) {
  double cx;
  int robot_grid_list[60];
  for (int i = 0; i < sizeof(robot_grid_list); i++) {
    robot_grid_list[i] = grid[grid_index-1][i];
  }
  cx = get_center_x(robot_grid_list[1], robot_grid_list[2], robot_grid_list[3], robot_grid_list[4]);
  return cx;
}

double environment :: get_y_center_of_grid(int grid_index) {
  double cy;
  int robot_grid_list[60];
  for (int i = 0; i < sizeof(robot_grid_list); i++) {
    robot_grid_list[i] = grid[grid_index-1][i];
  }
  cy = get_center_y(robot_grid_list[1], robot_grid_list[2], robot_grid_list[3], robot_grid_list[4]);
  return cy;
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
    for (int robot_index = 0; robot_index<NUM_ROBOTS; robot_index++) {

      cout << "For Robot " << robot_index << ": " << endl;
      
      int current_grid, next_grid;
      current_grid = server::get_current_grid_robot(robot_index);
      next_grid = server::get_next_grid_robot(robot_index);
      cout << "Next grid calculation completed." << endl;
      cout << "Current grid index is: " << current_grid << endl;
      cout << "Next grid index is: " << next_grid << endl;
      //move by speed towards next grid in the path
      //do we move up, down, left, or right?
      //get the X and Y of the next grid. Compare it to our X and Y.
      //Then move towards it.
      double myx = robotx[robot_index];
      double myy = roboty[robot_index];
      cout << "Current X is: " << myx << endl;
      cout << "Current Y is: " << myy << endl;
      //we have our x, our y, our current grid, and our next grid.
      //we need the desired x, desired y.
      //for this we need grid index ----> x and y
      double desiredx = get_x_center_of_grid(next_grid);
      double desiredy = get_y_center_of_grid(next_grid);
      cout << "Desired X is: " << desiredx << endl;
      cout << "Desired Y is: " << desiredy << endl;
    }
    
    wait(10000, SC_NS);
  }
}

