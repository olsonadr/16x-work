# Authors: S23, T05 (Nick Olson, Ty Brewen)
# For MIME 101 / CS 160 Fall 2018
# Assignment: Lab 4-5: Cozmo Task
# Date: 10/18/2018

import CozmOSU


# Variables
robot = CozmOSU.Robot()
speed = 50 # arbitrary speed value
timeout = 5 # arbitrary amount of time to timeout for cube location

def execute_step(robot, step):
    global speed, timeout
    command = step[: step.index(",")]
    argument = float(step[step.index(",")+1 :])

    if(command == "drive"):
        robot.driveForward(argument, speed) # argument is the distance to drive in mm
    elif(command == "turn"):
        robot.turn(argument) # argument is the degrees to turn from current rotation (left rotation is positive).
    elif(command == "cube"):
        robot.moveHead(argument) # argument is the rotation of Cozmo's head. argument == 0 implies straight ahead.
        cube = robot.getVisibleCube(timeout)
        try:
            robot.pickupCube(cube)
            pass
        except:
            print("RIP. No cube found.")
            pass
    elif(command == "drop"):
        robot.resetLift(robot)
        robot.driveForward(-10)


def main(robot):
    # Get steps from file. Sources: https://stackoverflow.com/a/3926003, https://stackoverflow.com/questions/7368789/convert-all-strings-in-a-list-to-int
    with open("steps_NEW.txt", "r") as file:
        for line in file:
            if line[0] == "#":
                continue
            execute_step(robot, line)

robot.start(main)