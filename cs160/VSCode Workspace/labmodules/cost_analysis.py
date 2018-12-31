import math
import os #Source: https://www.quora.com/Is-there-a-Clear-screen-function-in-Python

#Lab 2, 10/4/2018
#Nicholas Olson, Ty Brewen
#Dr. Mo

#Material cost constants
card_cost = .5 #per sq inch
tape_cost = .75 #per sq inch
straw_cost_per_straw = 1.0 #each, ~per 1.5 sq inch
straw_cost_per_in = float(straw_cost_per_straw/1.5) #per sq inch
cup_cost_per_cup = 2.0 #each, ~per 11 sq inch
cup_cost_per_in = float(cup_cost_per_cup / 11.0)

#Variables to be defined
card_amt = 0 #151.25
tape_amt = 0 #15
straw_amt = 0 #5
cup_amt = 0 #4

total_card_cost = 0
total_tape_cost = 0
total_straw_cost = 0
total_cup_cost = 0

total_combined_cost = 0

#Boolean values to be determined
straw_is_per_in = 0
cup_is_per_in = 0

#Take amount of each material used from user input
os.system("clear")
print("")

card_amt = float(input("Square inches of cardboard: "))
tape_amt = float(input("Square inches of masking tape: "))

straw_amt = float(input("Number of straws (input -1 if measured in sq in): "))
if straw_amt < 0:
	straw_amt = float(input("Square inches of straw: "))
	straw_is_per_in = 1

cup_amt = float(input("Number of plastic cups (input -1 if measured in sq in): "))
if cup_amt < 0:
	cup_amt = float(input("Square inches of cup: "))
	cup_is_per_in = 1

#Calculate total costs
total_card_cost = card_cost * card_amt
total_tape_cost = tape_cost * tape_amt

if straw_is_per_in == 1:
	total_straw_cost = straw_cost_per_in * straw_amt
else:
	total_straw_cost = straw_cost_per_straw * straw_amt

if cup_is_per_in == 1:
	total_cup_cost = cup_cost_per_in * cup_amt
else:
	total_cup_cost = cup_cost_per_cup * cup_amt

total_combined_cost = total_card_cost + total_tape_cost + total_straw_cost + total_cup_cost

#Print receipt, ascii source: http://www.network-science.de/ascii/
os.system("clear")
print("Inputs: \n[cardboard, tape, straws, cups]")
print("[" + str(total_card_cost) + ", " + str(total_tape_cost) + ", " + str(total_straw_cost) + ", " + str(total_cup_cost) + "]")
print("")
print("**--+------------ooO0000Ooo------------+--**")
print("  *-+----------------------------------+-*\n")
print("           Thanks for Shopping at")
print("   ______  __")
print("  /\\__  _\\/\\ \\      __")
print("  \\/_/\\ \\/\\ \\ \\___ /\\_\\    ___    ___")
print("     \\ \\ \\ \\ \\  _ `\\/\\ \\  /'___\\ /'___\\ ")
print("      \\ \\ \\ \\ \\ \\ \\ \\ \\ \\/\\ \\__//\\ \\__/")
print("       \\ \\_\\ \\ \\_\\ \\_\\ \\_\\ \\____\\ \\____\\ ")
print("        \\/_/  \\/_/\\/_/\\/_/\\/____/\\/____/")
print("        ~~BOYS GROCERIES AND MAYO!~~\n")
print(" *----------------------------------------*\n")
print("     Items                      Price")
print("     -----                      -----")
print("     Cardboard                 $" + str(total_card_cost))
print("     Masking Tape              $" + str(total_tape_cost))
print("     Straws                    $" + str(total_straw_cost))
print("     Plastic Cups              $" + str(total_cup_cost) + "\n")
print("                                Total")
print("                                -----")
print("                               $" + str(total_combined_cost) + "\n")
print(" *----------------------------------------*")
print("                                  __")
print("        _____ _           _      |  |")
print("       |_   _| |_ ___ ___| |_ ___|  |")
print("         | | |   | .'|   | '_|_ -|__|")
print("         |_| |_|_|__,|_|_|_,_|___|__|")
print("           and please come again!\n")
print("  *-+----------------------------------+-*")
print("**--+------------ooO0000Ooo------------+--**\n")