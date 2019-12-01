# Maze-Solver-Bot
## basic Idea
With the help of micro-controller and sensors, bot will follow a line and solve the maze.
##  Components Required
Arduino Nano/Uno, breadboard, breadboard wires, 3 LDR sensors, IC 7805, IC 7809, jumping wires, L293D motor driver IC, chasis, 12V battery.
## Design and Working
we have used LDR(light dependent resistors) to follow the line and sense the colour and send it to arduino, which further sends the signal to L293D IC, that drives the motor.IC 7805 is used to power LDR sensors and IC 7809 is used to power arduino. We have given priority as LEFT > STRAIGHT > RIGHT in order to solve the maze
## How to Run
copy this code to arduino IDE and upload to arduino.
