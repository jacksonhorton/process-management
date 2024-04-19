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

  //  Scheduler scheduler(algorithm::priority);
  //Scheduler scheduler(2);
  Scheduler scheduler(2);
  /*
   * TEST
   *
   */
  /*scheduler.add_process(0,4,3);
  scheduler.add_process(1,3,2);
  scheduler.add_process(2,1,2);
  scheduler.add_process(3,2,4);
  scheduler.add_process(4,5,5);*/
  scheduler.add_process(0,5,1);
  scheduler.add_process(1,4,1);
  scheduler.add_process(2,2,1);
  scheduler.add_process(4,1,1);
  
  
  //scheduler.add_process(0, 4, 3);
  scheduler.start();

  return 0;
}
