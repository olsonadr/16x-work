# Authors: S23, T05 (Nick Olson, Ty Brewen)
# For MIME 101 / CS 160 Fall 2018
# Assignment: Lab 4-5: Cozmo Task (Updated for Lab 5)
# Date: 10/22/2018

import CozmOSU

# Global Variables (I like Java style, okay?)
robot = CozmOSU.Robot()
speed = 100  # arbitrary speed value
timeout = 2  # arbitrary amount of time to timeout for cube location


# Methods for individual types of step a user can program:
def drive(distance):
    global robot
    global speed
    # argument was the distance to drive in mm
    robot.driveForward(distance, speed)


def turn(angle):
    global robot
    # argument was the angle to turn from current rotation in degrees (left rotation is positive).
    robot.turn(angle)


def cube(head_rotation):
    global robot
    global timeout
    # argument is rotation of head, 0 is best for looking on flat ground.
    robot.moveHead(head_rotation)

    rotation = 0
    cube = robot.getVisibleCube(timeout)
    while cube is None and rotation < 360: #While no cube is found and Cozmo has not searched full panorama for cube.
        turn(30)
        rotation += 30
        cube = robot.getVisibleCube(timeout)
    
    try:
        robot.pickupCube(cube)
        pass
    except:
        print("Whoopsie! No cube found.")
        pass


def drop(nerd):
    global robot
    robot.resetLift()
    robot.driveForward(-10)


# Method for parsing the line from the steps_NEW.txt file into code:
def execute_step(robot, step):
    global speed, timeout

    valid_commands = {
        "drive": drive,
        "turn": turn,
        "cube": cube,
        "drop": drop
    }

    command = step[: step.index(",")]
    argument = float(step[step.index(",")+1:])

    try:
        valid_commands[command](argument)
        pass
    except:
        print("Whoopsie! Bad instruction!")
        pass


# Main method to open and split steps_NEW.txt file into steps:
def main(robot):
    # Get steps from file. Sources: https://stackoverflow.com/a/3926003, https://stackoverflow.com/questions/7368789/convert-all-strings-in-a-list-to-int
    with open("steps_NEW.txt", "r") as file:
        for line in file:
            if line[0] == "#":
                continue
            execute_step(robot, line)


# GO!
robot.start(main)