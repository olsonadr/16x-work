import CozmOSU
import math

#Author: S23,T05, (Nick Olson, Ty Brewen)
#For MIME 101 / CS 160 Fall 2018
#Python code for navigating ramp 1
#This code does not follow template, typed in advance.

robot = CozmOSU.Robot()

in_to_mm_conversion = 25.4
cozmo_length = 88.9 #3.5in
speed = 100 #arbitrary speed value

initial_pitch = 0 #defining variable, 0 not used

#Multiplying flat distance by the secant (1/cos(pitch)) of the ramp pitch gives distance to travel along ramp:
def get_angled_length(flat_distance, pitch):
        result = (1 / math.cos(pitch)) * flat_distance
        return result

def execute_step(robot, step):
    global speed
    flat_distance = step[2] * in_to_mm_conversion #Converts step distance in inches to milimeters.
    angled_distance = 0

    robot.turn(step[0])

    if step[1] == 0: #step is on flat surface, not a ramp.
        '''robot.calibrateLevelPitch(2,100) #Old code using pitch detection (was too innaccurate for continued use)'''
        robot.driveForward(flat_distance, speed)
    else: #step is on a ramp, at some incline
        '''angled_distance = get_angled_length(flat_distance, robot.getCurrentPitch()) #Old code using pitch detection (was too innaccurate for continued use)'''
        angled_distance = get_angled_length(flat_distance, 8) #8 degrees is average ramp pitch found using pitches.py.
        robot.driveForward(angled_distance, speed)

def main(robot):
    '''global initial_pitch #Old code
    initial_pitch = robot.calibrateLevelPitch(5, 100) #Old code'''
    line_number = 0

    #Get steps from file. Sources: https://stackoverflow.com/a/3926003, https://stackoverflow.com/questions/7368789/convert-all-strings-in-a-list-to-int
    with open("steps_OLD.txt", "r") as file:
            for line in file:
                if line_number < 2:
                    line_number += 1
                    continue
                line = line.split(',', 3) #splitting each line (step) into the 3 numbers for rotation, ramp-hood, and distance
                line = list(map(float, line)) #each step has the angle difference to turn before moving,
                                                #whether the segment has an incline (1 or 0),
                                                #and the xy-plane distance to travel for that step.
                execute_step(robot, line)

    robot.say("Did I make it?")

robot.start(main)