#!/usr/bin/env python3
from ev3dev2.motor import LargeMotor, MediumMotor, OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D

# TODO:
l_wheel = LargeMotor(OUTPUT_B)
r_wheel = LargeMotor(OUTPUT_C)
s_motor = MediumMotor(OUTPUT_A)
# d_motor = MediumMotor(OUTPUT_D)

l_wheel.run_direct(speed_sp = 0)
r_wheel.run_direct(speed_sp = 0)
s_motor.run_forever(speed_sp = 0)
# d_motor.run_forever(speed_sp = 0)
