import CozmOSU

robot = CozmOSU.Robot()

in_to_mm_conversion = 25.4
speed = 50

initial_pitch = 0

def main(robot):
    global initial_pitch
    initial_pitch = robot.calibrateLevelPitch(5, 100)
    robot.driveForward(100, speed)
    print('Initial_Pitch, Pitch_On_Ramp:\n',str(initial_pitch),str(robot.getCurrentPitch()))

robot = CozmOSU.Robot()
robot.start(main)