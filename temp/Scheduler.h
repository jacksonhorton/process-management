#pragma once
#include "Manager.h"
#include <vector>

class Scheduler {
 private:
  int cpu_time;
  Manager manager;
  std::vector<int> add_order;
 public:
  Scheduler(Manager manager);
  void add_process(int pstart_time, int cpu_time_needed, int process_priority);
  void start();
  void run_process(int pid, int cpu_time);
};
