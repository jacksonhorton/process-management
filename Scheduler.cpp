#include "Scheduler.h"
#include <iostream>
#include <algorithm>

using namespace std;



//
// Algorithms for scheduling:
//


class FCFS : public ScheduleAlgorithm {
 public:
  void loop(Scheduler *scheduler) override {
    while (scheduler->manager.num_processes() > 0) {
      cout << "\nTime: " << scheduler->cpu_time << endl;

      if (scheduler->running == nullptr) {
	// get the process we should run scheduler cycle
	for (unsigned long i = 0; i < scheduler->add_order.size(); i++) {
	  process* p = scheduler->manager.get_process(scheduler->add_order[i]);
	  if (p->ptime_start > scheduler->cpu_time) {
	    // if the process hasn't arrived yet
	    continue;
	  }
	  else if (scheduler->running != nullptr && p->ptime_start >= scheduler->running->ptime_start) {
	    // if potential process has later (or equal) arrival/start time
	    continue;
	  }
	  
	  scheduler->running = p;
	  //break;
	  // TODO: don't overwrite the running process every time?
	}
      }
      
      
      // run the process
      if (scheduler->running != nullptr) {
	cout << "Running " << scheduler->running->pid << endl;
	scheduler->run_process(scheduler->running->pid, scheduler->quantum);
      }
      else {
	cout << "No process to run scheduler cycle" << endl;
      }
    
      
      // prepare for next cycle
      scheduler->manager.get_processes(scheduler->cpu_time);
      scheduler->cpu_time += scheduler->quantum;
    }
  };
};



// TODO: cpu_time may need to start at 1 for generating stats, not sure yet
Scheduler::Scheduler(algorithm a) : cpu_time(0), quantum(1) {
  switch(a) {
  case algorithm::fcfs:
    this->sort = FCFS::loop;
    break;
  default:
    this->sort = FCFS::loop; // fcfs is the default
    break;
  }
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
  
  //loop();
};

/*
void Scheduler::loop() {
  while (this->manager.num_processes() > 0) {
    cout << "\nTime: " << this->cpu_time << endl;

    if (this->running == nullptr) {
      // get the process we should run this cycle
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
    if (this->running != nullptr) {
      cout << "Running " << this->running->pid << endl;
      this->run_process(this->running->pid, this->quantum);
    }
    else {
      cout << "No process to run this cycle" << endl;
    }
    
      
    // prepare for next cycle
    this->manager.get_processes(this->cpu_time);
    this->cpu_time += this->quantum;
  }
};
*/

void Scheduler::run_process(int pid, int cpu_time) {
  process* p = this->manager.get_process(pid);
  
  p->cpu_time_remaining -= cpu_time; //if cpu_time/quantum isn't 1, may need to subtract time remaing from cpu_time to not take up the whole quantum, idk tho
  
  // check if process is ready to terminate
  if (p->cpu_time_remaining <= 0) {
    this->manager.terminate(pid);

    //management stuff
    this->running = nullptr; // reset the running process
    
    auto pid_it = find(this->add_order.begin(), this->add_order.end(), pid); // remove pid from add_order
    this->add_order.erase(pid_it);
  }

};
