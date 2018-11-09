//environment.cpp
//environment.cpp
#include "helper.h"
#include "environment.h"
#include "server.h"

//0 = Nothing, 1 = Acknowledged (Ack)
//int environment :: receive_message(int m) {
//  
//}

int environment :: message_received = 0; //0 = none received , 1 = ack received
double environment :: robotx[NUM_ROBOTS] = {};
double environment :: roboty[NUM_ROBOTS] = {};
double environment :: humanx[NUM_HUMANS] = {};
double environment :: humany[NUM_HUMANS] = {};
int environment :: stop_state[NUM_ROBOTS] = {};
int environment :: current_grid[NUM_ROBOTS] = {};
int environment :: grid[60][60] =
  { //row index 0
   {1, 0, 0, 2, 2}, {2, 2, 0, 4, 2}, {3, 4, 0, 6, 2}, {4, 6, 0, 8, 2}, {5, 8, 0, 10, 2}, {6, 10, 0, 12, 2}, {7, 12, 0, 14, 2},
   {8, 14, 0, 16, 2}, {9, 16, 0, 18, 2}, {10, 18, 0, 20, 2},
   //row index 1
   {11, 0, 2, 2, 4}, {12, 18, 2, 20, 4},
   //row index 2
   {13, 0, 4, 2, 6}, {14, 2, 4, 4, 6}, {15, 4, 4, 6, 6}, {16, 6, 4, 8, 6}, {17, 8, 4, 10, 6}, {18, 10, 4, 12, 6}, {19, 12, 4, 14, 6},
   {20, 14, 4, 16, 6}, {21, 16, 4, 18, 6}, {22, 18, 4, 20, 6},
   //row index 3
   {23, 0, 6, 2, 8}, {24, 10, 6, 12, 8}, {25, 18, 6, 20, 8},
   //row index 4
   {26, 0, 8, 2, 10}, {27, 2, 8, 4, 10}, {28, 4, 8, 6, 10}, {29, 6, 8, 8, 10}, {30, 8, 8, 10, 10}, {31, 10, 8, 12, 10},
   {32, 12, 8, 14, 10}, {33, 14, 8, 16, 10}, {34, 16, 8, 18, 10},  {35, 18, 8, 20, 10},
   //row index 5
   {36, 0, 10, 2, 12}, {37, 12, 10, 14, 12}, {38, 18, 10, 20, 12},
   //row index 6
   {39, 0, 12, 2, 14}, {40, 2, 12, 4, 14}, {41, 4, 12, 6, 14}, {42, 6, 12, 8, 14}, {43, 8, 12, 10, 14}, {44, 10, 12, 12, 14},
   {45, 12, 12, 14, 14}, {46, 14, 12, 16, 14}, {47, 16, 12, 18, 14}, {48, 18, 12, 20, 14},
   //row index 7
   {49, 0, 14, 2, 16}, {50, 18, 14, 20, 16},
   //row index 8
   {51, 0, 16, 2, 18}, {52, 2, 16, 4, 18}, {53, 4, 16, 6, 18}, {54, 6, 16, 8, 18}, {55, 8, 16, 10, 18},  {56, 10, 16, 12, 18},
   {57, 12, 16, 14, 18}, {58, 14, 16, 16, 18}, {59, 16, 16, 18, 18}, {60, 18, 16, 20, 18}
  };

double environment :: get_x_center_of_grid(int grid_index) {
  double cx;
  int robot_grid_list[20];
  int size_elements = sizeof(robot_grid_list)/sizeof(robot_grid_list[0]);
  for (int i = 0; i < size_elements; i++) {
    robot_grid_list[i] = grid[grid_index-1][i];
  }
  cx = get_center_x(robot_grid_list[1], robot_grid_list[2], robot_grid_list[3], robot_grid_list[4]);
  return cx;
}

double environment :: get_y_center_of_grid(int grid_index) {
  double cy;
  int robot_grid_list[20];
  int size_elements = sizeof(robot_grid_list)/sizeof(robot_grid_list[0]);
  for (int i = 0; i < size_elements; i++) {
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
  //INITIALIZATION -- ROBOT CURRENT GRID (IN SERVER) AND GPS XY (IN ENVIRONMENT)
  //initialize robot positions
  server::set_current_grid_robot(0, 1);
  server::set_current_grid_robot(1, 10);
  server::set_current_grid_robot(2, 49);
  server::set_current_grid_robot(3, 60);

  //set x and y in environment gps
  for (int robot_index = 0; robot_index<NUM_ROBOTS; robot_index++) {
    robotx[robot_index] = get_x_center_of_grid(server::get_current_grid_robot(robot_index));
    roboty[robot_index] = get_y_center_of_grid(server::get_current_grid_robot(robot_index));
  }

  cout << "INITIAL POSITIONS: " << endl;
  cout << "Robot 0 x is " << robotx[0] << endl;
  cout << "Robot 0 y is " << roboty[0] << endl;
  cout << "Robot 1 x is " << robotx[1] << endl;
  cout << "Robot 1 y is " << roboty[1] << endl;
  cout << "Robot 2 x is " << robotx[2] << endl;
  cout << "Robot 2 y is " << roboty[2] << endl;
  cout << "Robot 3 x is " << robotx[3] << endl;
  cout << "Robot 3 y is " << roboty[3] << endl;
  cout << "IS_GRID_OCCUPIED TESTS: " << endl;
  cout << "Grid 1 is " << server::is_grid_occupied(1) << endl;
  cout << "Grid 2 is " << server::is_grid_occupied(2) << endl;
  cout << "Grid 10 is " << server::is_grid_occupied(10) << endl;
  cout << "Grid 12 is " << server::is_grid_occupied(12) << endl;
  cout << "Grid 49 is " << server::is_grid_occupied(49) << endl;
  cout << "Grid 50 is " << server::is_grid_occupied(50) << endl;
  cout << "Grid 59 is " << server::is_grid_occupied(59) << endl;
  cout << "Grid 60 is " << server::is_grid_occupied(60) << endl;
  
  while(1) {
    //(1) MOVEMENT LOOP
    //Q: What is this robot? What is the next grid for this robot?
    //for each robot:
    //1. get the current grid and the next grid
    //2. update robot position
    for (int robot_index = 0; robot_index<NUM_ROBOTS; robot_index++) {

      //cout << "Movement Loop For Robot " << robot_index << ": " << endl;
      
      int current_grid, next_grid;
      current_grid = server::get_current_grid_robot(robot_index);
      next_grid = server::get_next_grid_robot(robot_index);
      //cout << "The Current Grid is: " << current_grid << endl;
      //cout << "The Next Grid is: " << next_grid << endl;
      //move by speed towards next grid in the path
      //do we move up, down, left, or right?
      //get the X and Y of the next grid. Compare it to our X and Y.
      //Then move towards it.
      double myx = robotx[robot_index];
      double myy = roboty[robot_index];
      //cout << "Current X is: " << myx << endl;
      //cout << "Current Y is: " << myy << endl;
      //we have our x, our y, our current grid, and our next grid.
      //we need the desired x, desired y.
      //for this we need grid index ----> x and y
      double desiredx = get_x_center_of_grid(next_grid);
      double desiredy = get_y_center_of_grid(next_grid);
      //cout << "Desired X is: " << desiredx << endl;
      //cout << "Desired Y is: " << desiredy << endl;
      //Now, we want to actually move towards the desired grid.
      //If desired is to the left of current, move left.
      //If desired is to the right of curent, move right.
      //If desired is above current, move up.
      //If desired is below current, move down.
      //movemment, so if we are not moving, don't do this
      if ((stop_state[robot_index]) == 0) {
	if (desiredx < myx) {
	  robotx[robot_index] -= SPEED_X;
	}
	else if (desiredx > myx) {
	  robotx[robot_index] += SPEED_X;
	}
	if (desiredy < myy) {
	  roboty[robot_index] -= SPEED_Y;
	}
	else if (desiredy > myy) {
	  roboty[robot_index] += SPEED_Y;
	}
      }
      //Boundary check
      //we are "crossing" if the distance between my gps and desired gps is <1.05.
      //at this point it would be safe to update the grid to the next grid.
      if (distance(myx, myy, desiredx, desiredy) < 1.05) {
	//Send CROSSING signal to server
	server::receive_message(robot_index, 1);
	wait(); //wait for a response
	//If "ack" is received, update current grid in server and keep going
	if (message_received == 1) {
	  stop_state[robot_index] == 0;
	  server::set_current_grid_robot(robot_index, next_grid);
	}
	//Otherwise, stop and change stop_state in env + status in server
	else {
	  stop_state[robot_index] == 1;
	  server::set_robot_status(robot_index, 1);
	}
      }
    }

    //Note. We wish to update the "current grid" and "next grid" in the server so that the path can be followed all the way to the end for each robot.
    //This will relate to the "crossing" signals.
    
    wait();
  }
}

void environment :: receive_message(int m) {
  message_received = m;
  cout << "environment message received" << endl;
}
