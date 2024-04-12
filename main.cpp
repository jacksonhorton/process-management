#include <iostream>
#include <limits>
#include "Manager.h"

using namespace std;
int main() {

  Manager myManager;
  myManager.add_process(1, 0, 10);

  string cmd = "";
  while (cmd != "4") {
    myManager.get_processes();
    cout << "(1) Add process\n(2) Change process state\n(3) Terminate process\n(4) Exit" << endl;
    cout << "Action? ";
    
    // get input
    getline(cin, cmd);

    if (cmd == "1") {
      int ptime, pstart, priority;
      cout << "\nEnter CPU time start of process: ";
      cin >> pstart;

      cout << "Enter amount of CPU time process needs: ";
      cin >> ptime;

      cout << "Enter the priority of the process: ";
      cin >> priority;

      
      myManager.add_process(priority, pstart, ptime);
    }
    else if (cmd == "2") {
      int pid;
      string new_state_input;
      process_state new_state;

      cout << "\nEnter PID: ";;
      cin >> pid;

      cout << "Which state? (running, ready, blocked, terminated) ";
      cin >> new_state_input;
      new_state = Manager::stringToState(new_state_input);

      myManager.change_state(pid, new_state);
    }
    else if (cmd == "3") {
      int pid;
      cout << "Enter pid of process to terminate: ";
      cin >> pid;

      myManager.terminate(pid);
    }
    
    cout << "\n\n\n\n";
    // clear cin to get rid of any newlines
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  
  myManager.simulate();

  return 0;
}
