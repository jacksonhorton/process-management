#include <string>
#include <map>

enum class process_state { ready=0, running=1, blocked=2 };

struct process {
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
  void add_process(int priority, int start_time, int time_required);
  void simulate();
  void get_processes();
  int change_state(int pid, process_state new_state);
  static std::string stateToString(process_state s);
  static process_state stringToState(std::string s);
};

