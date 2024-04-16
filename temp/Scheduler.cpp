#include "Scheduler.h"
#include <iostream>

using namespace std;

Scheduler::Scheduler(Manager manager) : cpu_time(0) {
  this->manager = manager;
  this->manager.get_processes();
};

void Scheduler::add_process(int pstart_time, int cpu_time_needed, int process_priority) {
  int pid = this->manager.add_process(process_priority, pstart_time, cpu_time_needed);
  if (pid < 0) {
    cout << "Error when trying to add process to manager from scheduler.";
    return;
  }
  else {
    // add pid to order vector to use during run
    this->add_order.push_back(pid);
  }
};

void Scheduler::start() {
  while (this->manager.num_processes() > 0) {
    vector<int> terminated_processes;
    for (int i=0; i< this->add_order.size(); i++) {
      
    }
  };
};

void Scheduler::run_process(int pid, int cpu_time) {
  process* p = this->manager.get_process(pid);
  
};
