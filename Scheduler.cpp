#include "Scheduler.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <queue>

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
    this->cpu_time += 1;
  }
}


void Scheduler::sjf_loop() {
  while (this->manager.num_processes() > 0) {
    cout << "\nTime: " << this->cpu_time << endl;
    
    if (this->running == nullptr) {
      // get the process we should run scheduler cycle
      for (unsigned long i = 0; i < this->add_order.size(); i++) {
	process* p = this->manager.get_process(this->add_order[i]);
	
	if (p->ptime_start > this->cpu_time) {
	  // process hasn't arrived yet
	  continue;
	}
	else if (this->running != nullptr) {
	  // a new running candidate has already been picked
	  if (p->cpu_total_time >= this->running->cpu_total_time) {
	    // process is not shorter than current candidate
	    continue;
	  }
	}
	
	this->running = p;
      }
    }
      
    
    // run the process
    this->run_process(this->running, 1);
    
      
    // prepare for next cycle
    this->manager.get_processes(this->cpu_time);
    this->cpu_time += 1;
  }
}



void Scheduler::priority_loop() {
  while (this->manager.num_processes() > 0) {

    if (this->running == nullptr) {
      for (unsigned long i = 0; i < this->add_order.size(); i++) {
	process* p = this->manager.get_process(this->add_order[i]);

	if (p->ptime_start > this->cpu_time) {
	  // process hasn't arrived yet
	  continue;
	}
	if (this->running != nullptr && this->running->priority <= p->priority) {
	  continue;
	}

	this->running = p;
      }
    }


    cout << "\nTime: " << this->cpu_time << endl;
    
    // run the process
    this->run_process(this->running, 1);
    
      
    // prepare for next cycle
    this->manager.get_processes(this->cpu_time);
    this->cpu_time += 1;
    
  }
}


void Scheduler::rr_loop() {
  queue<int> ready_queue = {};
  while (this->manager.num_processes() > 0) {
    
    // get the process we should run scheduler cycle
    for (unsigned long i = 0; i < this->add_order.size(); i++) {
      process* p = this->manager.get_process(this->add_order[i]);
	
      if (p->ptime_start > this->cpu_time) {
	// if process hasn't arrived yet
	continue;
      }

      
      // run the process
      cout << "\nTime: " << this->cpu_time << endl;
      this->running = p;
      int runtime = this->quantum;
      if (this->running->cpu_time_remaining - this->quantum < 0) {
	runtime = this->running->cpu_time_remaining;
      }
      
      this->run_process(this->running, runtime);

      
      // prepare for next cycle
      this->manager.get_processes(this->cpu_time);
      this->cpu_time += runtime;
    }
      
    

  }
}


//
//  Constructors
//
Scheduler::Scheduler(int quantum) : Scheduler(algorithm::rr, quantum) {
  
}

Scheduler::Scheduler() : Scheduler(algorithm::fcfs, 1) {
}

Scheduler::Scheduler(algorithm a) : Scheduler(a, 1) {
}

Scheduler::Scheduler(algorithm a, int quantum) : cpu_time(0) {
  this->alg = a;
  this->quantum = quantum;
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
  else if (this->alg == algorithm::priority) {
    cout << "Running with priority algorithm." << endl;
    this->priority_loop();
  }
  else if (this->alg == algorithm::rr) {
    cout << "Running with round-robin algorithm." << endl;
    this->rr_loop();
  }
  else {
    cout << "Invalid algorithm selection, cannot run scheduling." << endl;
    exit(1);
  }

  metrics m;
  m.total_time = this->cpu_time;
  m.avg_wait = (double) accumulate(this->wait_times.begin(), this->wait_times.end(), 0) / this->wait_times.size();
  m.avg_turnaround = (double) accumulate(this->turnaround_times.begin(), this->turnaround_times.end(), 0) / this->turnaround_times.size();
  
  cout << "\nTotal Time: " << m.total_time << endl;
  cout << "Average turnaround: " << m.avg_turnaround << endl;
  cout << "Average wait: " << m.avg_wait << endl;
  
};

void Scheduler::run_process(process* p, int cpu_time) {
  if (p != nullptr) {
    cout << "Running PID " << this->running->pid << " for " << cpu_time << " time" << endl;
  }
  else {
    cout << "No process to run scheduler cycle" << endl;
    return;
  }
  
  p->cpu_time_remaining -= cpu_time; //if cpu_time/quantum isn't 1, may need to subtract time remaing from cpu_time to not take up the whole quantum, idk tho
  
  // check if process is ready to terminate
  if (p->cpu_time_remaining <= 0) {
    // track metrics
    double turnaround = (this->cpu_time + cpu_time) - p->ptime_start;
    double wait = turnaround - p->cpu_total_time;
    this->wait_times.push_back(wait);
    this->turnaround_times.push_back(turnaround);
    
    this->manager.terminate(p->pid);

    //management stuff
    this->running = nullptr; // reset the running process
    
    auto pid_it = find(this->add_order.begin(), this->add_order.end(), p->pid); // remove pid from add_order
    this->add_order.erase(pid_it);
  }

};
