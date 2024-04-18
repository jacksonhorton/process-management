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
  void (*sort) (Scheduler);
  
 public:
  Scheduler(algorithm);
  Manager get_manager();
  void add_process(int pstart_time, int cpu_time_needed, int process_priority);
  void start();
  void run_process(int pid, int cpu_time);

  Manager manager;
  process* running = nullptr;
  std::vector<int> add_order;
  int cpu_time;
  int quantum;

};


// Base class for algorithms
class ScheduleAlgorithm {
public:
  virtual void loop(Scheduler *scheduler);
};

