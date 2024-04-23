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

  cout << "NOW RUNNING PRIORITY SCHEDULING" << endl;
  // Priority
  Scheduler priority_scheduler(algorithm::priority);
  priority_scheduler.add_process(0,5,1);
  priority_scheduler.add_process(1,4,1);
  priority_scheduler.add_process(2,2,1);
  priority_scheduler.add_process(4,1,1);
  priority_scheduler.add_process(6,5,1);
  // run scheduler
  priority_scheduler.start();

  cout << "\n\n\n\n\nNOW RUNNING SHORTEST JOB FIRST" << endl;
  // SJF
  Scheduler sjf_scheduler(algorithm::sjf);
  sjf_scheduler.add_process(0,5,1);
  sjf_scheduler.add_process(1,4,1);
  sjf_scheduler.add_process(2,2,1);
  sjf_scheduler.add_process(4,1,1);
  sjf_scheduler.add_process(6,5,1);
  // run scheduler
  sjf_scheduler.start();


  cout << "\n\n\n\n\nNOW RUNNING ROUND ROBIN" << endl;
  // Round robin
  Scheduler rr_scheduler(algorithm::rr);
  rr_scheduler.add_process(0,5,1);
  rr_scheduler.add_process(1,4,1);
  rr_scheduler.add_process(2,2,1);
  rr_scheduler.add_process(4,1,1);
  rr_scheduler.add_process(6,5,1);
  // run scheduler
  rr_scheduler.start();


  cout << "\n\n\n\n\nNOW RUNNING FIRST COME FIRST SERVE..." << endl;
  // Fcfs
  Scheduler fcfs_scheduler(algorithm::fcfs);
  fcfs_scheduler.add_process(0,5,1);
  fcfs_scheduler.add_process(1,4,1);
  fcfs_scheduler.add_process(2,2,1);
  fcfs_scheduler.add_process(4,1,1);
  fcfs_scheduler.add_process(6,5,1);
  // run scheduler
  fcfs_scheduler.start();
  return 0;
}
