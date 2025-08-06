# Elevator Simulation

This elevator simulation is meant to mimic an individual's experience with a physical elevator including waiting for an elevator, choosing your floor, dealing with other passengers, and more. The simulation can be accessed at https://replit.com/@RandomMaker/Elevator-Simulation?v=1.

## Features
1. Configurable Elevator: The ```int floors``` variable at the beginning of main.cpp can be altered to support an elevator with however many floors are desired.
2. User Input: The user can determine where they want to go with the elevator. They first specify whether they want to go up or down, just like you would waiting outside an elevator. Once the elevator reaches the user, they can press the floor they would like to go to and the elevator will drop them off.
3. Passengers: Simulates other people pressing buttons on the elevator at the same time as the user, adding to the realism of the experience.
4. Floor Prioritization: The elevator prioritizes which floor to go to based on two factors: the direction the user initially requested and the proximity of a selected floor to the current floor. With these two constraints, the elevator optimizes its travel path to efficiently transport its passengers.
5. Realism: The elevator has doors that open and shut, shows a status message once the user has boarded the elevator, and prints the current floor as well as arrival to the console. This makes working with the elevator very intuitive and straightforward.
