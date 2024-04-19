#pragma once
#include "Manager.h"
#include <vector>

struct metrics {
  double avg_wait;
  double avg_turnaround;
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
  std::vector<int> wait_times;
  std::vector<int> turnaround_times;
  algorithm alg;
  Manager manager;
  process* running = nullptr;

  void fcfs_loop();
  void sjf_loop();
  void priority_loop();
  void rr_loop();
  
  std::vector<int> add_order;
  int cpu_time;
  int quantum;

  Scheduler(algorithm a, int quantum);
  
  
 public:
  Scheduler();
  Scheduler(algorithm a);
  Scheduler(int quantum);
  Manager get_manager();
  void add_process(int pstart_time, int cpu_time_needed, int process_priority);
  void start();
  void run_process(process* p, int cpu_time);
};

