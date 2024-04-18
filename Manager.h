#pragma once
#include <string>
#include <map>

enum class process_state { ready, running, blocked, terminated };

struct process {
  int pid;
  int priority;
  int ptime_start;
  int cpu_time_remaining;
  process_state state;
};

/**
 * Manager for processes.
 *
 * @class Manager Manager.h "process_manager/Manager.h"
 * @brief Keeps track of processes and how much CPU time they need to simulate a CPU processing them.
 *
 */
class Manager {
 private:
  
  int pcounter;
  static const int max_processes = 50;
  std::map<int, process> processes;

public:
  
  Manager();
  int add_process(int priority, int start_time, int time_required);
  int terminate(int pid);
  void get_processes();
  void get_processes(int cpu_time); // show only processes that have arrived
  int change_state(int pid, process_state new_state);
  process* get_process(int pid);
  int num_processes();
  static std::string stateToString(process_state s);
  static process_state stringToState(std::string s);
};

