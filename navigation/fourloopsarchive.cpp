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
