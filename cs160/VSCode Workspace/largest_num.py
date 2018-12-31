import random  # random library source: https://docs.python.org/3/library/random.html

rand_nums = []

# \n is a line-break pushing the following text to the next line,
# it used later instead of the seperate print() calls shown here:
print('Welcome! Would you like your numbers to be randomly selected or inputed?')
print('Input 0 for randomly selected or 1 for inputed (by a friend)...')

# User chose random generation option:
if int(input('>>')) == 0:
    # Fill rand_nums list with random integers between 0 and 100, inclusively:
    for i in range(5):
		
		# randint() source: https://docs.python.org/3/library/random.html#random.randint
		# random.randint(a,b) returns random integer between a and b, inclusively.
        temp_num = random.randint(0, 100)

        # list.append(element) places the given element at the end of the given list.
        rand_nums.append(temp_num)

# User chose input option or tried to break the code with another number:
else:
    print('\nOkay! Please enter your 5 numbers, seperated by \",\" (commas) and no spaces:')

	# map() source: https://www.python-course.eu/python3_lambda.php
    	# list(map(int, list)) takes each element of the 'iterable' (in this case the list list)
		# and applies the method or function int to it, filling a new list with the results.
		# Example: Call of list(map(int, [1.1, 2.6, .3])) returns [1, 2, 0].
    # split() source: https://www.tutorialspoint.com/python3/string_split.htm
    	# str.split(',', 5) takes the str inputted and splits it into a list of up to 6 elements,
		# where the string is split each time it encounters the delimeter ',' up to 5 times.
		# Even if they put more than 6 items, it will only seprate the first 6 of them.
		# Example: Call of 'AbABbABCbD'.split('b', 2) returns ['A','AB','ABCbD'].
    rand_nums = list(map(int, input('>>').split(',')))
	

print('\nHere are your results:')

# Don't need this here or at all, but for added transparency, prints the list of random ints:
print('Your input:\n>>' + str(rand_nums))

# max_num set as first number in rand_nums box:
max_num = rand_nums[0]

# Finding biggest int in rand_nums using Python's way of express for each loops
# (for(int num : rand_nums) in Java) which, for each number num in the list rand_nums,
# executes the following block using that value for num:
for num in rand_nums:
    if(num >= max_num): #Compare
        max_num = num #Set max_num to this new greatest value

# Print this biggest int in rand_nums (stored in max_num):
print('\nLargest random integer in list:\n>>' + str(max_num))
print('\nThanks, and have a lovely day!')