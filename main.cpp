/**
 * @file main.cpp
 * @author Jackson Horton
 * @date 2024-04-15
 * @brief Creates a Manager object and lets the user interact with it.
 * 
 * The main function lets the user manage a Manager object using a CLI. The user can create processes, schedule processes, and terminate processes.
 */

#include <iostream>
#include <limits>
#include "Scheduler.h"

using namespace std;


int main() {

  Scheduler scheduler;

  scheduler.add_process(1, 2, 3);
  scheduler.add_process(5, 4, 3);
  scheduler.start();

  return 0;
}
