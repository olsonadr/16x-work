#!/usr/bin/env python3
from ev3dev2.motor import LargeMotor, MediumMotor, MoveSteering
from ev3dev2.motor import OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D
from ev3dev2.sensor import INPUT_1, INPUT_2, INPUT_3, INPUT_4
from ev3dev2.sensor.lego import GyroSensor, UltrasonicSensor, ColorSensor
import time, multiprocessing, logging
# Module / Library Sources:
	# ev3dev2 source:			 https://github.com/ev3dev/ev3dev-lang-python
	# Time source: 				 https://docs.python.org/2/library/time.html#time.time
	# Logging source:			 https://docs.python.org/3/library/logging.html
	# Multiprocessing Source:	 https://sebastianraschka.com/Articles/2014_multiprocessing.html
	# Keyboard Shortcuts: 		 https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf
	# Sys Source:				 https://docs.python.org/3/library/sys.html

# I added comments to try to increase the readability of the code, although the headers are not
#	always in the correct style, they get information across anyway. The logging calls can also
#	be used as a way to help understand the code while reading, but they were added to help with
#	the debugging process (and were incredibly useful)!
# Indented line like those above are a continuation of the thought expressed by the preceeding,
# 	whereas new lines generally are a new thought or piece of seperate information for you.
# Also, there are some lines of code that are commented out. These are either legacy code from our
#	alternate / prior solutions or they are code that was used for debugging purposes.

# TODO:
# Setting logging level:
logging.basicConfig(level = logging.DEBUG,
					format = '%(message)s')

# Initialization of motors and sensors:
logging.info('Program started.')
logging.debug('Modules Imported. Initializing motors.')
sorting_motor = MediumMotor(OUTPUT_A)
driving_motors = MoveSteering(OUTPUT_B, OUTPUT_C)
dumping_motor = MediumMotor(OUTPUT_D)

logging.debug('Initialized. Intializing sensors.')
gyro = GyroSensor(INPUT_1)
ultrasonic = UltrasonicSensor(INPUT_2)
front_color_sensor = ColorSensor(INPUT_3)
sorting_color_sensor = ColorSensor(INPUT_4)

# Initialization of constants and variables:
logging.debug('Initialized. Initializing misc global variables.')
driving_speed = 25
turning_speed = 15
sorting_speed = 25
dumping_speed = 5
time_for_dump = 2
time_for_sort = .5
degrees_to_sort = 90
degrees_to_reset = 180 # Resetting sorting system to neutral after a right-sort
degrees_to_dispense = 30 # MODIFY THIS VALUE
degrees_to_turn_before_dispensing = 5 # MODIFY THIS VALUE
arbitrary_value_from_testing = 42 # MODIFY THIS VALUE
angles_to_containers = []
pill_color_1 = 'Red'
pill_color_2 = 'Green'
pills_sorted = False
threshold_for_approaching_in_cm = 6
gyro_drift_rate = 0
overall_initial_time = time.time()
logging.info('All global variables initialized.\n')

# Assumes gyro has already been reset using reset_gyro() to establish the value of gyro_drift_rate.
def get_gyro_angle():
	global gyro, overall_initial_time
	return gyro.angle - gyro_drift_rate*(time.time() - overall_initial_time)

# Returns index of smallest value in the passed list.
# Pre-condition: passed list has length >= 1
def get_index_of_smallest_value(input_list):
	min_index = 0

	logging.debug('get_index_of_smallest_value():')
	logging.debug('Initial smallest value: input_list[{}] = {}'.format(min_index, input_list[min_index]))
	
	for index in range(len(input_list)):
		if input_list[index] < input_list[min_index]:
			min_index = index
			logging.debug('New current smallest value: input_list[{}] = {}'.format(min_index, input_list[min_index]))

	logging.debug('Found overall smallest value as: input_list[{}] = {}'.format(min_index, input_list[min_index]))
	logging.info('get_index_of_smallest_value() complete, returning.\n')

	return min_index

# Left hopper is pill_color_1 (used by sort_pills()) so put the current pill in left sub-hopper (tray).
def pill_to_left():
	global sorting_motor, sorting_speed, degrees_to_sort
	sorting_motor.on_for_degrees(sorting_speed, degrees_to_sort)
	logging.debug('Pill sent to left hopper. Sleeping.')
	# time.sleep(time_for_sort) # Not needed as adding a break actually decreases the accuracy of the color sensor.
	# logging.debug('Slept, returning.') # " " (ditto)
	return

# Right hopper is pill_color_2 (used by sort_pills()) so put the current pill in right sub-hopper (tray).
def pill_to_right():
	global sorting_motor, sorting_speed, degrees_to_sort
	sorting_motor.on_for_degrees(-1 * sorting_speed, degrees_to_sort)
	logging.debug('Pill sent to right hopper. Sleeping.')
	time.sleep(time_for_sort/2) # Time to let the pill fall out before resetting to neutral.
	sorting_motor.on_for_degrees(sorting_speed, degrees_to_reset)
	# time.sleep(time_for_sort)
	# logging.debug('Slept, returning.')
	return

# Uses alternate method of taking many samples of color in order to determine the color of the pill in the
# 	sorting chamber as color sensor will sometimes return a mix of black and red for red pills and will
# 	sometimes read green pills as black. The function returns black if green and red are not found whatsoever
#	to allow for me to adjust what the program does in this case in the sort_pills() function in the future.
def get_pill_color():
	global sorting_color_sensor

	logging.info('Determining color...')
	# 100 samples, as quickly as the sensor can output. If it detects red or green ever, return early.
	for i in range(100):
		current_color = sorting_color_sensor.color_name
		# logging.debug(current_color, end=' ')
		if current_color == 'Red': return 'Red'
		if current_color == 'Green': return 'Green'
		i # Just used to eliminate annoying 'unused variable i' warning by pylint.

	return 'Black'

# Assumes that the pills are properly loaded and no pill is in the color sensing chamber initially.
# There must be 10 pills and they must come in without gaps. Also assumes the color sensor is somewht reliable.
# Post-condition: pills are sorted into the two smaller hoppers from which they may be dispensed.
# 				  (expressed in commented code -->) Also calibrates the two pill colors (such that any colors of pills could work).
def sort_pills():
	global sorting_color_sensor, pill_color_1, pill_color_2, pills_sorted
	# left_is_calibrated = False # Legacy code referenced in function header.
	count = 0

	# sorting_color_sensor = front_color_sensor  # temp code

	logging.debug('sort_pills():')
	logging.debug('Initial target colors: {} & {}'.format(pill_color_1, pill_color_2))
	logging.debug('Pulling first pill into sorting chamber (call to left pill function).')

	# Pull first pill into the color-sensing chamber
	pill_to_left()
	pill_to_left()

	# Sort all pills into hoppers, doing some extra to account for hardware error leading
	# 	to gaps in the flow of pills (legacy -->) also calibrating colors as needed
	while count <= 12:
		current_color = get_pill_color()
		# current_color = sorting_color_sensor.color_name
		logging.debug('-\nPill {} detected as the color {}'.format(count, current_color))

		if pill_color_1 == current_color: # Read as red.
			logging.debug('Pill was pill_color_1, sending it to left (currently {}).'.format(pill_color_1))
			pill_to_left()
		else: # Green or black reading, because green is more often read as black than red and an empty chamber is black.
			logging.debug('Pill was pill_color_2, sending it to right (currently {}).'.format(pill_color_2))
			pill_to_right()

		# Legacy code referenced in function header:
		# else:
		# 	if pill_color_2 != current_color:
		# 		logging.debug('Pill necessitates calibration of the system.')
		# 		if not left_is_calibrated:
		# 			logging.debug('Pill was not color 1 or 2, calibrating pill_color_1 as {}.'.format(current_color))
		# 			pill_color_1 = current_color
		# 			left_is_calibrated = True
		# 			logging.debug('Sending pill to left (currently {}).'.format(pill_color_1))
		# 			pill_to_left()
		# 		else:
		# 			logging.debug('Pill was not color 1 or 2, calibrating pill_color_2 as {}.'.format(current_color))
		# 			pill_color_2 = current_color
		# 			logging.debug('Sending pill to right (currently {}).'.format(pill_color_2))
		# 			pill_to_right()
		# 	else:
		# 		logging.debug('Pill was pill_color_2, sending it to right (currently {}).'.format(pill_color_2))
		# 		pill_to_right()
		# time.sleep(3)

		count += 1

	logging.debug('All pills should be sorted correctly.')
	logging.info('sort_pills() complete, returning.\n')
	pills_sorted = True
	return 0

# rotate_to_angle:
# 	rotates the robot to face the value of desired_angle using the gyro and the two motors used for steering
# parameters:
# 	desired_angle:
# 		angle to turn to face
# pre-condition:
# 	desired_angle is an integer within range of possible gyro sensor outputs
# post-condition:
# 	robot has turned to face in direction of desired_angle, is within 4 degrees, max.
def rotate_to_angle(desired_angle):
	global driving_motors
	current_angle = get_gyro_angle()

	logging.debug('rotate_to_angles():')
	logging.debug('Finding whether left or right turn is more efficient.')
	logging.debug('current_angle = {}, desired_angle = {}'.format(current_angle, desired_angle))

	if current_angle > desired_angle:
		driving_motors.on(-100, turning_speed)
		logging.debug('Complete. Left turn necessary. Turning.')
	else:
		driving_motors.on(100, turning_speed)
		logging.debug('Complete. Right turn necessary. Turning.')

	logging.debug('Starting loop to check angle until delta < 2.')
	while True:
		current_angle = get_gyro_angle()
		# logging.error('Current angle = {}'.format(current_angle))
		# logging.error('Desired angle = {}'.format(desired_angle))
		# logging.error('Delta = {}'.format(abs(current_angle - desired_angle)))
		if abs(current_angle - desired_angle) < 2:
			logging.debug('Delta < 2, stopping wheels. Now facing desired_angle.')
			driving_motors.off(brake = True)
			logging.info('rotate_to_angle() complete, returning.\n')
			return

# Used when the robot starts pointing at first container so it does not need to be located as well.
# Uses the cone of vision of the ultrasonic sensor to determine the angle at which it can first see
# 	the second container, then the angle at which it can no longer see the second container, and then
#	uses an average of these values minus a constant offset to find the angle to the next container.
# Also accounts for the case in which the second container is close enough to the first container that
#	it is already visible after turning to place the first container out of view, by finding the angle
#	at which the second is no longer visible, and subtracting some arbitrary value we found in testing
#	that this angle was reliably offset from the desired bearing.
# Assumes the first container is no longer within view of the ultrasonic sensor.
def find_next_container():
	global driving_motors, ultrasonic, arbitrary_value_from_testing

	first_angle = 0
	second_angle = 0
	result = 0

	# If the next container is not already detected (ezpz)
	if(ultrasonic.distance_centimeters > 70):
		logging.debug('Starting motors to find next container.')
		driving_motors.on(100, turning_speed)
		while True:
			if ultrasonic.distance_centimeters < 70:
				logging.debug('Detected. Stopping.')
				driving_motors.off(brake = True)
				first_angle = get_gyro_angle()
				break

		logging.debug('Starting motors to find end of range of detection.')
		driving_motors.on(100, turning_speed)
		while True:
			if ultrasonic.distance_centimeters >= 70:
				logging.debug('Detected. Stopping.')
				driving_motors.off(brake = True)
				second_angle = get_gyro_angle()
				break

		result = (first_angle + second_angle) / 2 - 8

	else: # Container is already detected (less ezpz)
		logging.debug('Starting motors to find end of range of detection.')
		driving_motors.on(100, turning_speed)
		while True:
			if ultrasonic.distance_centimeters >= 70:
				logging.debug('Detected. Stopping.')
				driving_motors.off(brake = True)
				second_angle = get_gyro_angle()
				break
		
		result = second_angle - arbitrary_value_from_testing

	return result

# Searches 360 degree area around robot, returning a list with the two angles pointing
# 	toward the two closest objects (legacy function from prior solution)
def search_for_containers():
	global driving_motors, ultrasonic, angles_to_containers

	recorded_distances = []
	recorded_angles = []
	angles_of_shortest_distances = []
	initial_angle = get_gyro_angle()
	
	logging.debug('search_for_containers():')
	logging.debug('initial_angle = {}.'.format(initial_angle))
	logging.debug('get_gyro_angle() = {}.'.format(get_gyro_angle()))
	logging.debug('Starting wheels.')

	driving_motors.on(100, turning_speed)

	logging.debug('Recording all values for 310 degrees.')
	while abs(get_gyro_angle() - initial_angle) <= 300:
		# gyro.wait_until_angle_changed_by(3)
		distance = ultrasonic.distance_centimeters
		if distance < 80:
			recorded_angles.append(get_gyro_angle())
			recorded_distances.append(distance)

	logging.debug('Values recorded.')
	logging.debug('recorded_angles = {}.'.format(recorded_angles))
	logging.debug('recorded_distances = {}.'.format(recorded_distances))

	driving_motors.off(brake = True)

	logging.debug('Wheels stopped. Finding first shortest distance.\n')

	# Finds smallest value in distance list
	index = get_index_of_smallest_value(recorded_distances)
	angles_of_shortest_distances.append(recorded_angles[index])

	logging.debug('Found. Removing all distances within 20 degrees of this value.')

	# Removes all angles / distances within 20 degrees of this value, just in case.
	index = 0
	while index < len(recorded_angles):
		if abs(recorded_angles[index] - angles_of_shortest_distances[0]) <= 20:
			recorded_angles.pop(index)
			recorded_distances.pop(index)
		else:
			index += 1
		if index >= len(recorded_angles):
			break

	logging.debug('Removed. Finding new shortest distance.\n')

	# Finds smallest value in distance list, now that distances within 20 degrees of the first shortest distance have been removed.
	index = get_index_of_smallest_value(recorded_distances)
	angles_of_shortest_distances.append(recorded_angles[index])

	angles_to_containers = angles_of_shortest_distances
	logging.debug('Found. Angles of two shortest distances: {}.'.format(angles_of_shortest_distances))
	logging.info('search_for_containers() complete, returning.\n')
	return

# Drives the robot (in a straight line) up to the object directly ahead of it (pre-condition!),
# 	stopping when it gets within the distance in global variable 'threshold_for_approaching_in_cm'.
# 	Also determines the time it took the robot to reach this point using the time.time() function,
# 	so that it can be used to reverse the exact distance later in reverse().
def drive_to_object():
	global driving_motors, ultrasonic
	# initial_gyro = get_gyro_angle()
	initial_time = time.time()
	final_time = 0

	logging.debug('drive_to_object():')
	logging.debug('Turning driving motors on.')

	driving_motors.on(0, driving_speed)

	logging.debug('Motors on. Checking for need of termination of drive.')
	while True:
		if ultrasonic.distance_centimeters < threshold_for_approaching_in_cm:
			driving_motors.off(brake = True)
			logging.debug('Within distance threshold for approaching, stopping motors.')
			break

		# Legacy code from system that re-aligned the robot. Using MoveSteering eliminated the need for this.
		# if abs(get_gyro_angle() - initial_gyro) > 10:
		# 	logging.debug('Delta angle is > 10, turning to re-align with path.')
		# 	rotate_to_angle(initial_gyro)
		
		time.sleep(.1) # Cuts down on how many operations the robot must perform (closer is not a bad thing).

	logging.debug('Robot has driven up to the object and stopped.')
	logging.info('drive_to_object() complete, returning.\n')

	final_time = time.time()
	return	final_time - initial_time

# Drives the robot backward (in a straight line) for the duration passed (in seconds)
def reverse(time_to_travel):
	global driving_motors, driving_speed

	logging.debug('reverse():')
	logging.debug('Turning driving motors on, backward.')

	driving_motors.on(0, -1 * driving_speed)

	logging.debug('Waiting for time it took robot to travel to object.')
	time.sleep(time_to_travel)

	driving_motors.off(brake=True)

	logging.debug('Turning driving motors off.')
	logging.debug('Robot should now be back in the center of the field.')
	logging.info('reverse() complete, returning.')
	return

# Used by dump_appropriate_hopper(), empties left hopper of pills into container ahead.
def dump_left_hopper():
	global dumping_motor, pills_sorted, degrees_to_dispense
	dumping_motor.on_for_degrees(-1 * dumping_speed, degrees_to_dispense, brake = True)
	logging.debug('Left hopper opened, dumping for {} seconds.'.format(time_for_dump))

	# Legacy code: Used when multiprocessing is in effect in case run-time reaches this point
	# 		 	   while sorting, and sorting is not yet completed.
	# while not pills_sorted:
		# continue

	time.sleep(time_for_dump)
	dumping_motor.on_for_degrees(dumping_speed, degrees_to_dispense, brake = True)

	# Legacy debugging code when I was by myself and didn't have a dispensing system built.
	# global pills_sorted
	# while not pills_sorted:
	# 	continue
	# print('DUMPING LEFT!')

	logging.debug('Left hopper closed, pills dispensed.')
	return

# Used by dump_appropriate_hopper(), empties right hopper of pills into container ahead.
def dump_right_hopper():
	global dumping_motor, pills_sorted, degrees_to_dispense
	dumping_motor.on_for_degrees(dumping_speed, degrees_to_dispense, brake = True)
	logging.debug('Right hopper opened, dumping for {}seconds.'.format(time_for_dump))

	# Legacy code: Used when multiprocessing is in effect in case run-time reaches this point
	# 		 	   while sorting, and sorting is not yet completed.
	# while not pills_sorted:
	# 	continue

	time.sleep(time_for_dump)
	dumping_motor.on_for_degrees(-1 * dumping_speed, degrees_to_dispense, brake = True)

	# Legacy debugging code when I was by myself and didn't have a dispensing system built.
	# global pills_sorted
	# while not pills_sorted:
	# 	continue
	# print('DUMPING RIGHT!')

	logging.debug('Right hopper closed, pills dispensed.')
	return

# Uses the front_color_sensor to determine which container it is in front of (precondition!),
#	turns the robot to position the appropriate hopper above the container, and calls the right
#	function to dump the appropriate hopper.
def dump_appropriate_hopper():
	global driving_motors, front_color_sensor, degrees_to_turn_before_dispensing, pill_color_1, pill_color_2
	initial_gyro = get_gyro_angle()

	degrees = degrees_to_turn_before_dispensing

	logging.debug('dump_appropriate_hopper():')
	logging.debug('Getting color of container.')

	container_color = front_color_sensor.color_name
	container_is_color_1 = True # Default
	
	logging.debug('Container is {}.'.format(container_color))

	if container_color != pill_color_1: # Right hopper, must turn left and back
		degrees = -1 * degrees
		container_is_color_1 = False
	
	# This line is considered as an error by my linter now but worked fine until now, so comment as needed.
	logging.info('Container is color {color}, so robot must turn {direction} and back'.format_map({"color": (2,1)[container_is_color_1],
																								   "direction": ('right', 'left')[container_is_color_1]} ))

	logging.debug('Turning to place appropriate hopper above container.\n')
	# Rotate before dumping
	rotate_to_angle(initial_gyro + degrees)
	logging.debug('Turned. Calling appropriate dump function.\n')

	# Dump appropriate hopper
	if container_is_color_1: dump_left_hopper()
	else: dump_right_hopper()

	logging.debug('Dumped. Turning back.')

	# Rotate back
	rotate_to_angle(initial_gyro)
	
	logging.debug('Turned. Robot is now in alignment with center of field.')
	logging.info('dump_appropriate_pills() complete, returning.\n')
	return

# Resets the gyro and calculates the average rate of drift of the gyro to enable more accurate
# 	gyro readings from get_gyro_angle() later accounting for this annoying drift. Takes 30 samples
#	of the rate of change of the gyro over 3 seconds.
# Precondition: must be stationary to avoid innacurate resultant drift values.
def reset_gyro():
    global gyro, gyro_drift_rate, overall_initial_time
    gyro.reset
    time.sleep(1)
    overall_initial_time = time.time()
    logging.debug('Overall Initial Time = ' + str(overall_initial_time))
    average_gyro_rate = 0
    for i in range(30):
        average_gyro_rate += gyro.rate
        time.sleep(.1)
        i
    average_gyro_rate = average_gyro_rate / 30
    logging.debug('Average gyro rate = ' + str(average_gyro_rate))
    gyro_drift_rate = average_gyro_rate
    return

# Commands to approach and dump pills into the first container (if it is directly ahead).
# This also sorts the pills when already in front of the container, such that any pills that
# 	accidentally exit the trays we have for the sorted pills will not end up on the ground but in
# 	a container instead, which is preferable.
def first_container():
	time_driven = drive_to_object() - .5
	sort_pills()
	dump_appropriate_hopper()
	reverse(time_driven)

# Runs sort_pills and first_container functions in parallel (legacy, but still very usable)
# Commented code was unnecessary, as there were errors resulting from using the output queue
# 	and getting the returned values of these functions, so global variables were substituted
#	to eliminate the need of returned values whatsoever.
def sort_and_first_container():
	logging.debug('sort_search_and_drive():')

	# Defining the output queue
	# output_queue = multiprocessing.Queue()

	logging.debug('Setting up list of parallel processes to run.')

	# Setup a list of processes to run in parallel
	processes = [multiprocessing.Process(target = first_container),
				 multiprocessing.Process(target = sort_pills)]

	logging.debug('Set up. Starting parallel processes (search_for_containers and sort_pills).\n')

	# Start processes
	for p in processes:
		p.start()

	logging.debug('Exiting completed processes.')

	# Exit the completed processes
	for p in processes:
		p.join()

	# logging.debug('Getting results of processes from output queue.')

	# # Get process results from the output queue
	# results = [output_queue.get() for p in processes].remove(0)
	
	# logging.debug('Parallel processing output: {}.'.format(results))
	# logging.debug('Returned value (two shortest angles as list): {}.'.format(results[0]))
	
	return
	# return results[0]

# Legacy main function, using the search_for_containers() function required for the solution
#	if the team is not able to angle the robot initially as they wish.
def legacy_main():
	global angles_to_containers
	reset_gyro()
	search_for_containers()

	for container in range(2):
		# Getting to the container
		rotate_to_angle(angles_to_containers[container])
		distance_driven = drive_to_object()

		# Dump and get back to center of field
		dump_appropriate_hopper()
		reverse(distance_driven-.5)

	print('Success?\n')
	return

# Newest main execution and flow of solution. Allows for parallel processing to be used or not,
# 	although the sort_pills() line in first_container() must be removed to enable the full use
#	of either option as intended when this function was written.
def new_main():
	reset_gyro()
	# sort_and_first_container() # Option 1
	# sort_pills() # Option 2
	first_container() # Option 2

	# Now back at center of field ready to find next container
	rotate_to_angle(get_gyro_angle() + 70) # Getting first container out of view of ultrasonic sensor.
	rotate_to_angle(find_next_container()) # find_next_container rotates to find the next container using the ultrasonic sensor.
	time_driven = drive_to_object() - .5 # Records the time it takes to drive up to this container.
	dump_appropriate_hopper()
	reverse(time_driven) # Reverses back to center of field.
	print('\nSuccess?!')

# GO GO GO!
new_main()