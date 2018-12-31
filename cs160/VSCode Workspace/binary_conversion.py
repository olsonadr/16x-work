def main():
	base_input = 0
	base_result = 0
	temp_num = 0
	mid_step = 0
	input_num = 0
	result_list = []
	result = 0

	print("\n\nWelcome to my number base-conversion tool!\nPlease supply some information! (Max base-10).")
	base_input = int(input("  What is the base of your input: "))
	input_num = temp_num = int(input("  What is your input number:      "))
	base_result = int(input("  What is your desired base:      "))

	#Convert to base_10:
	i = 0
	while temp_num > 0:
		mid_step += (base_input ** i) * (temp_num % 10) #last digit * the place's value
		temp_num //= 10
		i += 1
	
	#Remainder method to convert to desired base:
	while(mid_step > 0):
		result_list.append(mid_step % base_result)
		mid_step //= base_result
	
	i = 0
	while i < len(result_list):
		result += (10 ** i) * result_list[i]
		i += 1

	result_list.reverse()

	print('\nResults:','\n   Base, Input:', str(base_input) + ',', str(input_num))
	print('   Base, Result:', str(base_result) + ',', str(result_list),"\n            or:", str(result), "\n")

main()