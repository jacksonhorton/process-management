#include <iostream>
#include "Manager.h"

using namespace std;


Manager::Manager() : pcounter(0) {
  cout << "Created Manager at " << pcounter << "." << endl;
}


void Manager::add_process(int priority, int start_time, int time_required) {
  if (pcounter >= Manager::max_processes) {
    cout << "Process limit reached, not added." << endl;
    return;
  }
  
  process p = { priority,
		start_time,
		time_required,
		process_state::ready };

  this->processes.insert({ this->pcounter, p });
  this->pcounter++;
}

void Manager::simulate() {

}

void Manager::get_processes() {
  cout << "Processes:" << endl;

  for (const auto& pair : this->processes) {
    //cout << key << ": " << Manager::stateToString(value.state) << endl;
    cout << "\t" << pair.first << ": " << stateToString(pair.second.state)
	 << ", starts @ time " << pair.second.ptime_start << ", "
	 << pair.second.cpu_time_remaining << " remaining." << endl;
  }

}


int Manager::change_state(int pid, process_state new_state) {

  map<int, process>::iterator pair = this->processes.find(pid);
  
  if (pair == this->processes.end()) {
    cout << "PID " << pid << " not found." << endl;
    return 0;
  }

  cout << "PID " << pid << " state is currently " << Manager::stateToString(pair->second.state) << endl;

  // change to new state
  pair->second.state = new_state;

  cout << "\tPID " << pid << " state is now " << Manager::stateToString(pair->second.state) << endl;
  
  return 1;
}


string Manager::stateToString(process_state s) {
  switch (s) {
  case process_state::ready:      return "Ready";
  case process_state::running:    return "Running";
  case process_state::blocked:    return "Blocked";
  default:                        return "Error";
  }
}


process_state Manager::stringToState(string s) {
  if (s == "ready") {
    return process_state::ready;
  }
  else if (s == "running") {
    return process_state::running;
  }
  else if (s == "blocked") {
    return process_state::blocked;
  }
  exit(1);
}

