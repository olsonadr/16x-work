# Author: Nicholas Olson
# CS 160 - Fall, 2018
# Dr. Jennifer Parham-Mocello
# Assignment 5
# Date: 11/25/2018

import random

guesses = ''
complete_string = ''
current_hidden_list = []
number_of_strikes = 0
canned_phrases = ['Wow CS is such a good major',
                  'I lOvE ProgRAmmINg',
                  'Eiffel Tower',
                  'Je mapelle Nicolas',
                  'Hello',
                  'Bonjour',
                  'Amazing']

# Passed solution of puzzle, returns the completely hidden string using underscores
#   for each letter character in the phrase but spaces still included.
# Returns 0 if 
def construct_hidden_list():
    global complete_string, guesses, current_hidden_list
    result = []

    for index in range(len(complete_string)):
        if complete_string[index] == ' ':
            result.append(' ')
        elif guesses.find(complete_string[index].lower()) >= 0:
            result.append(complete_string[index])
        else:
            result.append('_')

    current_hidden_list = result

    return result

# Checks if the guess is a valid character and len == 1 (assumes it is a string)
# Returns 0 if it is valid, 1 if it is len > 1, 2 if it is not a valid character
def check_valid_guess(input):
    input = str(input)
    if not input.isalpha(): return 2
    elif len(input) != 1: return 1
    else: return 0

# Checks if the proposed phrase is made of valid characters (assumes can be cast to string)
# Returns 0 if it is valid, 1 if it has invalid characters
def check_valid_phrase(input):
    input = str(input)
    for char in input:
        if not char.isalpha() or char.isspace():
            return 1
    return 0


# Checks if a given guess is a good guess (returns 0), a bad guess (returns 1), or has been guessed (returns 2)
def check_guess(guess):
    global complete_string, guesses
    guess = guess.lower()
    if guesses.lower().find(guess) >= 0: return 2
    if complete_string.lower().find(guess) >= 0: return 0
    else: return 1

# Print appropriate ascii art based on number_of_strikes
def print_art():
    global number_of_strikes
    
    # Completed:
        # print('*---++----\\')
        # print('    ||    |')
        # print('  (O__o)  |')
        # print('  /|  |\  |')
        # print('   |  |   |')
        # print('    ||    |')
        # print('          |')
        # print('_________/|\_')

    # Conditional, seperate lines:
        # print('*---++----\\')
        # print('    ||    |')
        # print(('   (())   |', '  (O__o)  |')[number_of_strikes >= 1] )
        # print(('   ', '  /')[number_of_strikes >= 3] + ('    ', '|  |')[number_of_strikes >= 2] + ('   |', '\\  |')[number_of_strikes >= 4] )
        # print(('          |', '   |  |   |')[number_of_strikes >= 2] )
        # print(('     ', '    |')[number_of_strikes >= 5] + ('     |', '|    |')[number_of_strikes >= 6] )
        # print('          |')
        # print('_________/|\_')

    # Conditional, combined line:
    print('\n*---++----\\\n    ||    |\n'+('   (())   |', '  (O__o)  |')[number_of_strikes >= 1]+'\n'+('   ', '  /')[number_of_strikes >= 3]+('    ', '|  |')[number_of_strikes >= 2]+('   |', '\\  |')[number_of_strikes >= 4]+'\n'+('          |', '   |  |   |')[number_of_strikes >= 2]+'\n'+('     ', '    |')[number_of_strikes >= 5]+('     |', '|    |')[number_of_strikes >= 6]+'\n          |\n_________/|\\_\n')

def print_guesses():
    global guesses
    result = ''
    for char in guesses:
        result += char + ' '
    print(result)
    return

def print_hidden_list():
    global current_hidden_list
    result = ''
    for element in current_hidden_list:
        result += element + ' '
    print(result)
    return

def game_setup():
    global complete_string, number_of_strikes, guesses
    guesses = ''
    number_of_strikes = 0
    print('Welcome to Hangman(tm)!')
    while True:
        print('\nWould you like to choose your own secret phrase (0) or have one generated (1)?')
        print('(Please only input an int, I don\'t want to put work into this program).')
        user_input = int(input('>>'))

        if user_input == 0:
            while True:
                print('\n  Enter secret phrase (must be comprised only of alpha characters ([a-z] or [A-Z]) and spaces):')
                user_phrase = input('  >>')
                validity = check_valid_phrase(user_phrase)
                if validity == 0:
                    complete_string = user_phrase
                    break
                else:
                    print('  **Why would you use invalid characters? Try again.')
            break
        elif user_input == 1:
            complete_string = canned_phrases[int(random.random()*len(canned_phrases))]
            break
        else:
            print('\n  **That\'s not one of the choices. Try again.')
            continue
    
    construct_hidden_list()
    game_iteration()

    return

def game_iteration():
    global number_of_strikes, guesses, current_hidden_list, complete_string
    print('\n---------------------------\n\nOur beautiful boy:')
    print_art()
    print('Guessed Letters:')
    print_guesses()
    print('\nStrikes:\n' + str(number_of_strikes))
    print('\nCurrent Hidden Phrase:')
    print_hidden_list()

    # Get guess and check it.
    while True:
        print('\nGuess a letter: (a-z or A-Z)')
        guess = input('>>')
        validity = check_valid_guess(guess)
        if validity == 1:
            print('\n**Must be a single letter! Try again.')
            continue
        elif validity == 2:
            print('\n**Invalid character option! Try again.')
            continue
        correctness = check_guess(guess)
        if correctness == 2:
            print('\n**You already guessed that! Try again.')
            continue
        guesses += guess
        if correctness == 1:
            number_of_strikes += 1
            break
        else:
            break

    construct_hidden_list()

    if number_of_strikes >= 6:
        print('\n---------------------------\n\nYou lose!')
        print_art()
        print('The phrase was:\n\'' + complete_string + '\'')
    else:
        for char in current_hidden_list:
            if char == '_':
                game_iteration()

        print('\n---------------------------\n\nYou win!')
        print_art()
        print('The phrase was:\n\'' + complete_string + '\'')
    
    print('\nPlay again? (0 or 1) ((I don\'t care if you purposefully break this, you\'re done either way.))')
    user_input = int(input('>>'))
    if user_input == 1:
        print('\n\n')
        game_setup()
    else:
        print('See ya!')
        exit()

game_setup()