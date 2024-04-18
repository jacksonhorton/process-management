#include "Scheduler.h"
#include <__config>
#include <iostream>
#include <algorithm>

using namespace std;

//
// Algorithms for scheduling:
//
void Scheduler::fcfs_loop() {
  while (this->manager.num_processes() > 0) {
    cout << "\nTime: " << this->cpu_time << endl;

    if (this->running == nullptr) {
      // get the process we should run scheduler cycle
      for (unsigned long i = 0; i < this->add_order.size(); i++) {
	process* p = this->manager.get_process(this->add_order[i]);
	if (p->ptime_start > this->cpu_time) {
	  // if the process hasn't arrived yet
	  continue;
	}
	else if (this->running != nullptr && p->ptime_start >= this->running->ptime_start) {
	  // if potential process has later (or equal) arrival/start time
	  continue;
	}
	  
	this->running = p;
	//break;
	// TODO: don't overwrite the running process every time?
      }
    }
    
      
    // run the process
    this->run_process(this->running, 1);
      
      
    // prepare for next cycle
    this->manager.get_processes(this->cpu_time);
    this->cpu_time += this->quantum;
  }
};

void Scheduler::sjf_loop() {
  while (this->manager.num_processes() > 0) {
    cout << "\nTime: " << this->cpu_time << endl;

    if (this->running == nullptr) {
      // get the process we should run scheduler cycle
      for (unsigned long i = 0; i < this->add_order.size(); i++) {
	process* p = this->manager.get_process(this->add_order[i]);

        if (this->running != nullptr && p->cpu_total_time < this->running->cpu_total_time) {
	  this->running = p;
	}

      }
    }
    
    
    // run the process
    this->run_process(this->running, 1);
    
      
    // prepare for next cycle
    this->manager.get_processes(this->cpu_time);
    this->cpu_time += this->quantum;
  }
};





Scheduler::Scheduler() : Scheduler(algorithm::fcfs) {

}


// TODO: cpu_time may need to start at 1 for generating stats, not sure yet
Scheduler::Scheduler(algorithm a) : cpu_time(0), quantum(1) {
  this->alg = a;
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
  this->running = nullptr;
  
  if (this->alg == algorithm::fcfs) {
    cout << "Running with first-come, first-serve algorithm." << endl;
    this->fcfs_loop();
  }
  else if (this->alg == algorithm::sjf) {
    cout << "Running with shortest-job first algorithm." << endl;
    this->sjf_loop();
  }
};

void Scheduler::run_process(process* p, int cpu_time) {
  //process* p = this->manager.get_process(pid);
  if (p != nullptr) {
    cout << "Running " << this->running->pid << endl;
  }
  else {
    cout << "No process to run scheduler cycle" << endl;
    return;
  }
  
  p->cpu_time_remaining -= cpu_time; //if cpu_time/quantum isn't 1, may need to subtract time remaing from cpu_time to not take up the whole quantum, idk tho
  
  // check if process is ready to terminate
  if (p->cpu_time_remaining <= 0) {
    this->manager.terminate(p->pid);

    //management stuff
    this->running = nullptr; // reset the running process
    
    auto pid_it = find(this->add_order.begin(), this->add_order.end(), p->pid); // remove pid from add_order
    this->add_order.erase(pid_it);
  }

};
