# Author: Nicholas Olson
# CS 160 - Fall, 2018
# Dr. Jennifer Parham-Mocello
# Assignment 4
# Date: 11/15/2018

# Reflection (Extra-Credit):
# My approach did not change all that much after reviewing other students' plans. It clarified to me that I hadn't fully completed my plan though.
# I changed the approach in that my calculation functions no longer return a value, but print out their result before passing the runtime back
# to the main menu function for a potential next iteration with refreshed variables. I could have incorporated things like 'character.isdigit()'
# for input validation, but I felt like that was unduly outside the scope of the class and I already had something functional. I did implement
# using 'string'.format(args) this time because of something I saw in one of my reviewee's code last assignment, and I love it.

# Implementation:
def check_if_integer(string_input):
	for index in range(len(string_input)):
		character = string_input[index]

		if(
			not((character >= '0' and character <= '9') or
				(len(string_input) > 1 and index == 0 and character == '-'))
		):
			print('*Error! Input is not an integer!*')
			return False

	return True


def check_if_natural_number(int_input):
    if int_input <= 0:
        print('*Error! Input is not greater than 0!*')
        return False

    return True


def check_if_float(string_input):
	count_of_points = 0
	for index in range(len(string_input)):
		character = string_input[index]

		if(character == '.'):
			count_of_points += 1

		if(
			count_of_points > 1 or
			not((character >= '0' and character <= '9') or
				(len(string_input) > 1 and index == 0 and character == '-'))
		):
			print('*Error! Input is not an float!*')
			return False

	return True

# prompt is string prompt for user input
# indentation_level int is how indented the prompt and input should be (for prettiness of outputs)
def get_integer_input(prompt, indentation_level):
	indentation_string = ''
	if indentation_level != 0:
		for i in range(indentation_level - 1):
			indentation_string += '  '

	while True:
		print('\n' + indentation_string + prompt)
		user_input = input(indentation_string + '>>')

		if check_if_integer(user_input):
			user_input = int(user_input)
			break
	
	return user_input


# same parameters, checks if >0 too
def get_natural_number_input(prompt, indentation_level):
    indentation_string = ''
    if indentation_level != 0:
        for i in range(indentation_level - 1):
            indentation_string += '  '

    while True:
        print('\n' + indentation_string + prompt)
        user_input = input(indentation_string + '>>')
        
        if check_if_integer(user_input):
            if check_if_natural_number(int(user_input)):
                user_input = int(user_input)
                break

    return user_input


# The function being integrated:
def f(x):
	return x**2


# rectangle_approximation:
# 	Calculate approximate integral of f(x) using a left-hand rectangle riemann-sum.
# parameters:
#	lower_bound: 			The lower bound of the interval of values on which
# 							the integral of f(x) is evaluated.
#	upper_bound: 			The upper bound of the interval of values on which
# 							the integral of f(x) is evaluated.
#	number_of_trapezoids: 	The number of rectangles the interval is divided
# 							into for the approximation of the integral.
# returns:
#	result_of_approximation:	The value of the integral approximation.
def rectangle_approximation(lower_bound, upper_bound, number_of_rectangles):
	result_of_approximation = 0
	width_of_rectangle = (upper_bound - lower_bound) / number_of_rectangles

	for rectangle in range(number_of_rectangles):
		height = f(lower_bound + (rectangle * width_of_rectangle))
		result_of_approximation += height * width_of_rectangle

	return result_of_approximation


# trapezoid_approximation:
# 	Calculates approximate integral of f(x) using trapezoidal riemann-sum:
# parameters:
#	lower_bound: 			The lower bound of the interval of values on which
# 							the integral of f(x) is evaluated.
#	upper_bound: 			The upper bound of the interval of values on which
# 							the integral of f(x) is evaluated.
#	number_of_trapezoids: 	The number of trapezoids the interval is divided
# 							into for the approximation of the integral.
# returns:
#	result_of_approximation:	The value of the integral approximation.
def trapezoid_approximation(lower_bound, upper_bound, number_of_trapezoids):
	result_of_approximation = 0
	width_of_trapezoid = (upper_bound - lower_bound) / number_of_trapezoids

	for trapezoid in range(number_of_trapezoids):
		height_1 = f(lower_bound + (trapezoid * width_of_trapezoid))
		height_2 = f(lower_bound + ((trapezoid + 1) * width_of_trapezoid))
		average_height = (height_1 + height_2) / 2
		result_of_approximation += average_height * width_of_trapezoid

	return result_of_approximation


def summation_calculation(lower_bound, upper_bound):
	result_of_approximation = 0
	for x in range(lower_bound, upper_bound + 1):
		result_of_approximation += f(x)

	return result_of_approximation


# Get user values and send user either to rectangle or trapezoid summation methods:
def integration_menu():
	print('\n\nIntegration Approximation:')
	print('  Rectangle (0) or Trapezoid (literally anything else):')
	user_selection = input('  >>')

	# Sets selection_is_rectangle to True if the condition [user_selection == 0] is true, False otherwise.
	selection_is_rectangle = (False, True)[user_selection == '0']

	# Get values that will be passed to one of the methods as arguments.
	while True:
		lower_bound = get_integer_input('Lower bound of integration approximation (integer):', 2)
		upper_bound = get_integer_input('Upper bound of integration approximation (integer):', 2)
		if lower_bound <= upper_bound:
			break
		else:
			print('Invalid inputs! Lower bound must be <= upper bound')
	
	number_of_slices = get_natural_number_input(str('Number of '+('trapezoids', 'rectangles')[selection_is_rectangle]+' (positive integer, more ==> greater accuracy):'), 2)

	# Run function for selected method of integral approximation.
	if selection_is_rectangle:
		print('\nResult:\n  For f(x) = (x)^2:\n    Integral of f(x) on ({}, {}) = {}.'.format(lower_bound, upper_bound, rectangle_approximation(lower_bound, upper_bound, number_of_slices)))
	else:
		print('\nResult:\n  For f(x) = (x)^2:\n    Integral of f(x) on ({}, {}) = {}.'.format(lower_bound, upper_bound, trapezoid_approximation(lower_bound, upper_bound, number_of_slices)))

	# Back to main menu.
	return


# Get user values and send user to integration_calculation method:
def summation_menu():
	print('\n\nSummation Calculation:')

	# Get values that will be passed to one of the methods as arguments.
	lower_bound = get_integer_input('Lower bound (or starting value of x) of sum (integer):', 1)
	upper_bound = get_integer_input('Upper bound (or last value of x) of sum (integer):', 1)
	
	# Run function for calculating the sum.
	print('\nResult:\n  For f(x) = (x)^2:\n    Sum of f(x) on ({}, {}) = {}.\n\n'.format(lower_bound, upper_bound, summation_calculation(lower_bound, upper_bound)))

	return


# Main Menu: (Code is copied whole-sail from my last calculator program for assignment 3).
def main():
	print('\n*------------------------------------------------------------------*')
	print('Nick Olson\'s Totally Tubular Summation and/or Integration Calculator\n\n')
	print('Main Menu:\n----------')

	while True:
		# Get users preference as to summation or integration mode:
		print('\nChoose a calculation mode:')
		print('  Input \'S\' to start summation calculations.')
		print('  Input \'I\' to start integratal approximations.')
		print('  Input \'exit\' to close this program')
		user_input = input('  >>')

		# Interpret user input:
		if user_input.upper() == 'S':
			summation_menu()
		elif user_input.upper() == 'I':
			integration_menu()
		elif user_input.upper() == 'EXIT':
			break
		else:
			if not(user_input == str(user_input)):
				print('\n    Input was not a string, please try again...')
			else:
				print('\n    Input not a valid option, please try again...\n')
			continue
		
	print('\n\nWell fine then. I guess this is good-bye.')
	print('Thank you for spending this time with me!')
	print('*---------------------------------------*\n')

	return

#Go Time!
main()
