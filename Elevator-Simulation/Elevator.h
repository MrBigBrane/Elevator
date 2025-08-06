#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

class Elevator {
public:
    Elevator(int floors);

    void ButtonPress(int desFloor, bool user); // Simulate someone pressing elevator button
    void ExternalReq(string dir); // Simulate someone requesting elevator to come to their floor
    void Moving(); // Elevator begins traversing through requested floors
    void PrintElevatorStatus(); // Status message

private:
    string direction; // direction the elevator is travelling
    int numFloors; // total number of floors
    int currFloor; // current elevator floor
    int userFloor; // current user floor
    vector<pair<int, bool>> pressedFloors; // vector containing key value pairs of all buttons pressed. int represents requested floor and bool represents whether the individual pressing the button was the user or not
};

#endif 