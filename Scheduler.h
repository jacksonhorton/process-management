#pragma once
#include "Manager.h"
#include <vector>

struct metrics {
  double avg_wait_time;
  int total_time;
};

/**
 * First-come, first-serve
 * Shortest job first
 * Round Robin
 * Priority Scheduling
 */
enum class algorithm {fcfs, sjf, rr, priority};

class Scheduler {
 private:
  algorithm alg;
  Manager manager;
  process* running = nullptr;

  void fcfs_loop();
  void sjf_loop();
  
  std::vector<int> add_order;
  int cpu_time;
  int quantum;
  
  
 public:
  Scheduler();
  Scheduler(algorithm a);
  Manager get_manager();
  void add_process(int pstart_time, int cpu_time_needed, int process_priority);
  void start();
  void run_process(process* p, int cpu_time);
};

