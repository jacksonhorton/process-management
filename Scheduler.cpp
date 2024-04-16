#include "Scheduler.h"
#include <iostream>

using namespace std;

Scheduler::Scheduler() : cpu_time(0), quantum(1) {
  
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
  this->manager.get_processes();

  
  while (this->manager.num_processes() > 0) {
    cout << "\nTime: " << this->cpu_time << endl;
    
    process* p;
    for (int i = 0; i < this->add_order.size(); i++) {
      int pid = this->add_order[i];
      process* p_i = this->manager.get_process(pid);

      if (p->ptime_start <= this->cpu_time) {
	// process should run
	run_process(pid, this->quantum);
	break;
      }
    }
    this->manager.get_processes();
    this->cpu_time += this->quantum;
  }
};

void Scheduler::run_process(int pid, int cpu_time) {
  process* p = this->manager.get_process(pid);
  
  p->cpu_time_remaining -= cpu_time; //if cpu_time/quantum isn't 1, may need to subtract time remaing from cpu_time to not take up the whole quantum, idk tho
  
  // check if process is ready to terminate
  if (p->cpu_time_remaining <= 0) {
    this->manager.terminate(pid);
    //management stuff
    this->add_order.erase(this->add_order.begin()); // remove first element?
  }

};
