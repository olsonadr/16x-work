#!/usr/bin/env python3

from ev3dev2.sensor import INPUT_1, INPUT_2, INPUT_3, INPUT_4
from ev3dev2.sensor.lego import GyroSensor, UltrasonicSensor, ColorSensor
# from ev3dev2.motor import MediumMotor, OUTPUT_A
import logging, time, multiprocessing, argparse

# TODO:
gyro = GyroSensor(INPUT_1)
ultrasonic = UltrasonicSensor(INPUT_2)
front_color_sensor = ColorSensor(INPUT_3)
try:sorting_color_sensor = ColorSensor(INPUT_4)
except: pass

# sorting_motor = MediumMotor(OUTPUT_A)

gyro_drift_rate = 0
overall_initial_time = time.time()

logging.basicConfig(level = logging.DEBUG,
					format = '%(message)s')

def get_gyro_angle():
	global gyro, overall_initial_time
	return gyro.angle - gyro_drift_rate * (time.time() - overall_initial_time)

def reset_gyro():
    global gyro, gyro_drift_rate, overall_initial_time
    gyro.reset
    time.sleep(1)
    overall_initial_time = time.time()
    logging.debug('Overall Initial Time = ' + str(overall_initial_time))
    average_gyro_rate = 0
    for i in range(50):
        average_gyro_rate += gyro.rate
        time.sleep(.05)
        i
    average_gyro_rate = average_gyro_rate / 50
    logging.debug('Average gyro rate = ' + str(average_gyro_rate))
    gyro_drift_rate = average_gyro_rate
    return

def main():
    global gyro, ultrasonic, front_color_sensor,sorting_motor
    reset_gyro()
    time.sleep(1)
    while True:
        logging.debug('\n\n----\nGyro Raw:         {}'.format(gyro.angle))
        logging.debug('Gyro Accounted:   {}'.format(get_gyro_angle()))
        logging.debug('Ultrasonic:       {}'.format(ultrasonic.distance_centimeters))
        logging.debug('Front Color:      {}\n----\n\n'.format(front_color_sensor.color_name))
        # logging.debug('Sorting Color:    {}'.format(sorting_color_sensor.color_name))
        time.sleep(.5)

main()