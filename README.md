# systemc
ese 356

## adder
A simple combinational full adder

## communications
A simple communications interface

## cpu
A RISC CPU implementation

HOW TO COMPILE:
> export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
> g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 
-Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o main main.cpp alu.cpp controller.cpp 
dm.cpp pm.cpp rf.cpp  -lm -lsystemc

HOW TO RUN:
> ./main

## seq_det
A sequence detector for value "1011"

## two_counters
A variable countdown timer using two counters
