#include <cstdio>

#include <GoProgram.hpp>
#include <iostream>

//we should have something to manager inputs from the manager
//something to manage our outputs

//GoProgram class serves as intermediary between game && the brain manager
//game class serves as wrapper for AI class and board class

//Ideas: try to take advantage of the BEGIN command, you basicaly have 5 seconds of free calculation to start thinking ahead

int main() {
    GoProgram GoProgram;

    GoProgram.startInputLoop();
}