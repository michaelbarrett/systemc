#include "environment.h"
#include "robot.h"
#include "server.h"

int sc_main(int argc, char* argv[]) {
  //ports decl

  //parameters for paramaterized modules
  int path[5] = {0, 1, 2, 3, 4};

  //module instantiation
  environment en1("en1", &path[0]);
}
