import CozmOSU
import math

robot = CozmOSU.Robot()
diagonal_d = 1090.0 #(diagonal distance)
cozmo_length = 100
speed = 50.0

initial_pitch = 0
last_pitch = 0
curr_pitch = 0

curr_pos = 0
ramp_length = 0
ramp_height = 127

distance_to_go = 0

stage = 0

def main(robot):
    global diagonal_d, cozmo_length, speed, initial_pitch,last_pitch, curr_pitch, curr_pos, ramp_length, ramp_height, distance_to_go, stage

    initial_pitch = robot.calibrateLevelPitch()

    while stage == 0: #rotating
        robot.turn(math.degrees(math.atan(2/3)))
        stage += 1

    while stage == 1: #driving until on slope
        robot.driveForward(1, 1)
        curr_pos += 1
        curr_pitch = robot.calibrateLevelPitch()

        if(curr_pitch == last_pitch and curr_pitch != initial_pitch): #assumes constant slope ramp
            stage += 1
    
        last_pitch = curr_pitch

    while stage == 3: #calculating distance to drive
        ramp_length = diagonal_d - cozmo_length
        ramp_length = (ramp_length**2) + (ramp_height**2)
        ramp_length = math.sqrt(ramp_length)
        distance_to_go = ramp_length + (cozmo_length / 2)
        stage += 1
    
    while stage == 4: #driving up rest of ramp
        robot.driveForward(distance_to_go, speed)
        robot.driveForward(cozmo_length/2, speed)
        stage += 1

    robot.start(main)