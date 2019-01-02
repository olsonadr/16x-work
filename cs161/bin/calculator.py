# Author: Nicholas Olson
# CS 160 - Fall, 2018
# Dr. Jennifer Parham-Mocello
# Assignment 3
# Date: 10/22/2018

# Methods for allowed operations:
# Adds num_1 and num_2:
def add(num_1, num_2):
	return num_1 + num_2

# Subtracts num_2 from num_1:
def subtract(num_1, num_2):
	return num_1 - num_2

# Multiplies num_1 and num_2:
def multiply(num_1, num_2):
	return num_1 * num_2

# Divides num_1 by num_2:
def divide(num_1, num_2):
	return num_1 / num_2

# Raises num_1 to the power of num_2:
def power(num_1, num_2):
	return num_1 ** num_2
# End of methods for allowed operations.

# Methods for allowed calculator modes:
# Method for when programmer mode is selected, handles all base conversions:
def programmer_mode():
	print('\n\nProgrammer Mode:\n----------------')
  
	# Loop for each conversion so they can do it again at the end, if they wish:
	while True:
		# Listing variables that will be used:
		base_of_input = desired_base = temp_num = input_num = -1 # Set to -1 so future loops will operate as do-while loops
		result_num = mid_step = 0
		result_num_list = []

		# Get the number to convert and what it's base is from the user:
		while(input_num < 0 or input_num != int(input_num)):
			print('\n  Positive integer to convert:')
			try:
				input_num = temp_num = int(input('    >>')) # Set temp_num to this input as well so it can be modified later on without losing track of what the original value was.
				pass
			except:
				print('\n    I said a positive *integer*.')
				print('    Please try again, nerd...')
				pass
			else:
				if(input_num < 0):
					print('\n    I said a *positive* integer.')
					print('    Please try again, nerd...')
				pass
		
		while(base_of_input < 2 or base_of_input > 10):
			print('\n  Base of inputted number, 2 to 10:')
			print('    (2 for binary, 10 for decimal, etc.)')
			try:
				base_of_input = int(input('    >>'))
				pass
			except:
				print('\n    Why\'d you do that?')
				print('    So rude. Try again...')
				pass
			else:
				if(base_of_input < 2 or base_of_input > 10):
					print('\n    I said the base must be *2-10*.')
					print('    Please try again, nerd...')
				pass

		# Get the desired base from the user:
		while(desired_base < 2 or desired_base > 10):
			print('\n  Desired base for conversion, 2 to 10:')
			try:
				desired_base = int(input('    >>'))
				pass
			except:
				print('\n    AHHHHH! MY CODE IS ON FIRE...')
				print('    Just kidding. Try again...')
				pass
			else:
				if(desired_base < 2 or desired_base > 10):
					print('\n    Can you follow instructions?')
					print('    *2 to 10*. Try again, nerd...')
				elif(desired_base == base_of_input):
					print('\n    I could let you waste our time with this,')
					print('    but I\'d rather let you try again...')
					desired_base = 0
				pass

		#Convert input_num to base-10 by multiplying each place by the value of that place:
		counter = 0 # Counter for the power of the place (10^counter for each place in base-10).
		while temp_num > 0:
			mid_step += (base_of_input ** counter) * (temp_num % 10) #last digit * the place's value
			temp_num //= 10
			counter += 1
		# mid_step variable now holds the same value of input_num (which was stored in temp_num), but in base-10.

		# Remainder method to convert base-10 mid-step variable to desired base, placing each digit into a list to make the place deliniation more clear:
		while mid_step > 0:
			result_num_list.append(mid_step % desired_base) # Remainder step, taking remainder having divided by the desired-base.
			mid_step //= desired_base # Using integer division to ignore remainder.

		# Convert mid_step to desired base with multiplication method used in the first conversion of input_num to base-10; store this value in result_num in reverse order:
		counter = 0 # Same as before, counter is used as a counter variable for tracking the values of each place.
		for counter in range(len(result_num_list)):
			result_num += (10 ** counter) * result_num_list[counter] #len(result_num_list) - (counter + 1)]

		# This commented line is a built-in method to reverse the order of this list:
		# result_num_list.reverse()

		print('\n  Result:',   '\n   ', str(input_num), '==>', str(result_num))
		print('    base-' + str(base_of_input), '==> base-' + str(desired_base))

		# Check to see if the user wants to continue with the programmer mode again:
		while True:
			print('\n  Do another conversion? (\'Y\' or \'N\'):')
			user_input = input('    >>')
			if user_input.upper() == 'N':
				return
			elif user_input.upper() == 'Y':
				break
			else:
				print('\n    Are you doing this on purpose?')
				print('    Seriously? Please try again...\n')

	print('\n\nConversions complete. Returning to menu...')
	print('------------------------------------------')


# Method for when scientific mode is selected, handles all simple operations:
def scientific_mode():
	# Listing variables used in method.
	curr_result = 0
	line = ''
	line_list = []
	operand_1 = ''
	operand_2 = ''

	legal_operators = {
		'+': add,
		'-': subtract,
		'*': multiply,
		'/': divide,
		'**': power
	}
	legal_operands = {
		# All real numbers.
		'': curr_result,
		'ans': curr_result
	}

	print('\n\nScientific Mode:\n----------------\n')
	print('  Rules:\n  ------')
	print('    Limit to two operands and one operator per step.')
	print('    YOU MUST USE SPACES BETWEEN EVERY ELEMENT!')
	print('      Examples: \'5 + 5\' or \'9 ** 6\'.\n')
	print('    You may begin line a space and operator to operate on the last result as first operand.')
	print('    You may also use the keyword \'ans\' (lowercase) to represent the prior answer.')
	print('      Examples: \' + 8\' or \'5 ** ans\'.\n')
	print('    Operands can be integers, floating point numbers, or the str \'ans\' but not any other type.\n')
	print('    Operators can be \'+\', \'-\', \'*\', \'/\', or \'**\', but nothing else.\n')
	print('    To stop executing these operations, input \'exit\' with no characters before the word.\n')
	print('    Lastly, this calculator does not handle order of operations or multiple operators, so don\'t try.\n\n')
	
	print('  Operations:\n  -----------')

	while True:
		# Restate this dictionary so curr_result is correctly referenced:
		legal_operands = {
			# All real numbers.
			'': curr_result,
			'ans': curr_result
		}

		# Get input from user:
		line = input('    >>')

		# Check to see if user is done:
		if line == 'exit':
			break

		# Split line into a list of strings for interpretation:
		line_list = line.split(' ')

		# Determine operands:
		try:
			operand_1 = float(line_list[0])
			pass
		except:
			try:
				operand_1 = legal_operands[line_list[0]]
				pass
			except:
				print('\n    Invalid first operand or syntax!')
				print('    Follow the rules. Try again...\n')
				continue
			pass

		try:
			operand_2 = float(line_list[2])
			pass
		except:
			try:
				operand_2 = legal_operands[line_list[2]]
				pass
			except:
				print('\n    Invalid second operand or syntax!')
				print('    Follow the rules. Try again...\n')
				continue
			pass
		
		# Do operation and print new curr_result:
		try:
			curr_result = legal_operators[line_list[1]](operand_1, operand_2)
			pass
		except:
			print('\n    Invalid operator or syntax!')
			print('    Follow the rules. Try again...\n')
			continue
		
		# Displays curr_result without decimal if it is not needed:
		if curr_result == int(curr_result):
			print('                                ', str(int(curr_result)),'\n')
		else:
			print('                                ', str(curr_result),'\n')
	
	print('\n\nOperations complete. Returning to menu...')
	print('-----------------------------------------')
# End of methods for allowed calculator modes.


# Method for 'main menu' from which user chooses their calculator's mode:
def main_menu():
	# Variables to be used:
	user_input = ''
	is_first_execution = True

	print('\n*-------------------------------------*')
	print('Nick Olson\'s Totally Tubular Calculator\n\n')

	print('Main Menu:\n----------\n')
	while True:
		# Really not necessary, just for the cheeky interactions:
		if not is_first_execution:
			print('\n\nMain Menu:\n----------\n')
			print('  Oh, welcome back, my friend.')
			print('  Nice to see you here again!')
			print('  You know what to do now...\n')

		# Get users preference as to programmer or scientific mode:
		print('  Choose a calculation mode:')
		print('    Input \'P\' to enter Programmer Mode')
		print('      (for base conversions like decimal to binary).')
		print('    Input \'S\' to enter Scientific Mode')
		print('      (for simple mathematical operations like 5+5).')
		print('    Input \'exit\' to close this program')
		print('      (but why would you ever want to do that, bub)?\n')
		user_input = input('    >>')

		# Interpret user input:
		if user_input.upper() == 'P':
			programmer_mode()
		elif user_input.upper() == 'S':
			scientific_mode()
		elif user_input.upper() == 'EXIT':
			break
		else:
			print('\n    Wow, really? This was the easiest question in the calculator.')
			print('    You\'re dissappoint me so much right now. Please try again...\n')
			continue
		
		is_first_execution = False
	
	print('\n\nWell fine then. I guess this is good-bye.')
	print('Thank you for spending this time with me!')
	print('*---------------------------------------*\n')

#Go Time!
main_menu()
