#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include "Elevator.h"
#include <cstdlib>
#include <thread> 
#include <chrono> 
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <cmath>


using namespace std;

// Simulate the opening of elevator doors
void Open() { 
   cout << "Doors opening..." << endl;
   this_thread::sleep_for(chrono::milliseconds(500)); // delay for realism
   cout << "Doors opened!" << endl;
   this_thread::sleep_for(chrono::milliseconds(500)); // delay for realism
}

// Simulate the closing of elevator doors
void Close() { 
   cout << "Doors closing..." << endl;
   this_thread::sleep_for(chrono::milliseconds(500)); // delay for realism
   cout << "Doors closed!" << endl;
   this_thread::sleep_for(chrono::milliseconds(500)); // delay for realism
}

// Sets elevator to default position/settings
Elevator::Elevator(int floors) {
   numFloors = floors;
   direction = "up";
   currFloor = 1;
   userFloor = 1;
}

// Externally requesting elevator to come to user's floor
void Elevator::ExternalReq(string dir) {
   cout << "You are on floor " << userFloor << endl;
   
   if(currFloor - userFloor > 0) { // defines whether elevator should head up or down to meet user
      direction = "down";
   }
   else {
      direction = "up";
   }
   int startFloor = currFloor; // sets the floor from which the elevator starts for use in for loop
   
   for (int i = 0; i < abs(startFloor - userFloor); ++i) { // go up/down one floor until the elevator is on the same floor as the user
      if(direction == "up") { // go up one floor
         ++currFloor;
         cout << "Current Floor: " << currFloor << "\t" << "Direction: Heading " << direction << endl;
         this_thread::sleep_for(chrono::milliseconds(500));
      }
      else if(direction == "down") { // go down one floor
         --currFloor;
         cout << "Current Floor: " << currFloor << "\t" << "Direction: Heading " << direction << endl;
         this_thread::sleep_for(chrono::milliseconds(500));
      }
   }
   
   cout << "*Ding* The elevator has arrived on floor " << currFloor << endl;
   Open();
   cout << "You have entered the elevator." << endl;
   Close();
   
   direction = dir; // direction of the elevator set to the direction the user requested initially outside the elevator
} 

// Inserts floor number pressed in vector containing all buttons pressed
// Prioritizes which floor to go to first based on direction requested by user and proximity to the current floor of the elevator
void Elevator::ButtonPress(int desFloor, bool user) {
   this_thread::sleep_for(chrono::milliseconds(500));
   cout << "Button Pressed: " << desFloor << endl; // Outputs the button pressed

   int newDesFloor;
   pair<int, bool> button(desFloor, user); // pair created to store whether the floor selected was selected by the user or not
   
   auto alreadyPressed = find_if( pressedFloors.begin(), pressedFloors.end(), // checks whether the current button selected has already been selected in the elevator using a lambda function
    [desFloor] (pair<int, bool>& element) { return element.first == desFloor; } );

   if(desFloor == currFloor) { // the elevator should not store button presses that lead to the floor that the elevator is already on
      cout << "Passenger has requested to go to the floor they are currently on. Please try again." << endl;
      while(desFloor == currFloor) { // continually asks for a floor number until valid
         newDesFloor = rand() % 9 + 1;
         cout << "Button Pressed: " << newDesFloor << endl;
      }
      button.first = newDesFloor;
      pressedFloors.push_back(button); // pushes pair to the vector containing all button presses
   }
   else if(alreadyPressed != pressedFloors.end()) { // if the button selected has already been pressed then the elevator does not process the request again
      cout << "This button has already been pressed." << endl;
      return;
   }
   else {
      pressedFloors.push_back(button);
   }
   
   if(pressedFloors.size() > 0) { // filtering process is only necessary if there is more than one button pressed. in this code however, this never occurs.
      if(direction == "up") {
         sort(pressedFloors.begin(), pressedFloors.end(), [this](const pair<int, bool>& a, const pair<int, bool>& b) { // sorts the buttons pressed based on proximity to the current floor
               if(a.first - currFloor < 0 && b.first - currFloor < 0) {
                  return pow(1.00 / (a.first - currFloor), 2) > pow(1.00 / (b.first - currFloor), 2); // if both floors being compared are below the current floor, then whichever one is farther is placed later
               }
               else {
                  return 1.00 / (a.first - currFloor) > 1.00 / (b.first - currFloor); // Using the inverse of the distance allows simultaneously ordering by proximity to the current floor and prioritizing floors that are higher than the current floor rather than                                                                                              lower but closer
               }
           });
      }
      else { // sorting rule changes if the elevator is going down vs. up
         sort(pressedFloors.begin(), pressedFloors.end(), [this](const pair<int, bool>& a, const pair<int, bool>& b) {
               if(currFloor - a.first < 0 && currFloor - b.first < 0) {
                  return pow(1.00 / (currFloor - a.first), 2) > pow(1.00 / (currFloor - b.first), 2);
               }
               else {
                  return 1.00 / (currFloor - a.first) > 1.00 / (currFloor - b.first);
               }
           });
      }
   }
   
}

// Process of taking passengers to their destinations
void Elevator::Moving() {
   while(pressedFloors.size() > 0) { // loop runs until all floors have been reached
      bool key = true;
      auto userPresent = find_if( pressedFloors.begin(), pressedFloors.end(), // lambda function checks whether the floor pressed by the user is passed or yet to be reached --> user is onboard or not
       [key] (pair<int, bool>& element) { return element.second == key; } );
      
      if(pressedFloors.at(0).first - currFloor > 0) { // Redundancy to ensure that direction the elevator heads in is correct relative to the first destination
         direction = "up";
         if(userPresent != pressedFloors.end()) { // Only prints in console if the user is onboard. Otherwise, the floors other passengers reach is irrelevant.
            cout << "Going up..." << endl;
         }
      }
      else if(pressedFloors.at(0).first - currFloor < 0) {
         direction = "down";
         if(userPresent != pressedFloors.end()) {
            cout << "Going down..." << endl;
         }
      }
      int i;
      int startFloor = currFloor;
      for (i = 0; i < abs(pressedFloors.at(0).first - startFloor); ++i) // loop to head to first floor in pressedFloors vector
         {
            if(userPresent != pressedFloors.end()) { // only prints in console if user is onboard
               cout << "Floor " << currFloor << endl;
               this_thread::sleep_for(chrono::milliseconds(500));
            }
            if(direction == "up") {
               currFloor = currFloor + 1;
            }
            else if (direction == "down") {
               currFloor = currFloor - 1;
            }
         }
      if(userPresent != pressedFloors.end()) {
         userFloor = currFloor;
         cout << "Arrived at Floor " << currFloor << endl;
      }
      pressedFloors.erase(pressedFloors.begin()); // removes the floor that has just been reached
   }
   
}

void Elevator::PrintElevatorStatus() {
   cout << "\n*******" << endl;
   cout << "Current Floor: " << currFloor << "\t" << "Direction: Heading " << direction << endl;
   cout << "Buttons Pressed: ";
   for (auto floor : pressedFloors) {
      cout << floor.first << ", ";
   }
   cout << endl << "*******\n" << endl;
} 

