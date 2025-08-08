#include <iostream>
#include <string>
#include "Elevator.h"
#include <cstdlib>

using namespace std;

int main() { 
  int floors = 50; // set num of floors for the elevator
  
  Elevator elevator(floors); // declare elevator object
  string dir;
  int desFloor;

  srand(10); // seed randomization process for reproducable results

  cout << "Where would you like to go? (\"up\", \"down\" or -1 to exit): ";
  cin >> dir; // take in user input
  
  while(dir != "-1") { // break from loop if user requests to exit the program
    while(dir != "up" && dir != "down") { // input validation continually asks for direction until either "up" or "down"
      cout << "Invalid direction. Where would you like to go? (up/down): ";
      cin >> dir;
    }
  
    elevator.ExternalReq(dir); // Externally requests elevator to come to user's current floor
  
    cout << "Which floor would you like to go to: ";
    cin >> desFloor; 
    while(desFloor > floors || desFloor <= 0) { // input validation to ensure user's inputted floor number is within elevator range
      cout << "Invalid floor number pressed. Which floor would you like to go to: ";
      cin >> desFloor;
    }
  
    elevator.ButtonPress(desFloor, true); // user button press
    elevator.ButtonPress(rand() % (floors - 1) + 1, false); // simulation of random passenger
    elevator.ButtonPress(rand() % (floors - 1) + 1, false); // simulation of random passenger
    elevator.ButtonPress(rand() % (floors - 1) + 1, false); // simulation of random passenger
    elevator.PrintElevatorStatus(); // Provide elevator information
    elevator.Moving(); // Begin elevator transportation process

    cout << "Where would you like to go? (up/down or -1 to exit): "; // Once user has been unloaded, ask where they would like to go again
    cin >> dir;
  }

  return 0;
}
