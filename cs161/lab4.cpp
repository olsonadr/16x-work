#include <iostream>

/*
**  Function:			a_to_i
**  Parameters:			character - the character to be converted
**  Return Value:       the decimal representation of the character passed
**  Pre-Conditions:     the input is a character
**  Post-Conditions:    returned the decimal value of the character
*/
int a_to_i(char character)
{
	return static_cast<int>(character);
}

/*
**  Function:			i_to_a
**  Parameters:			decimal - the int to be converted
**  Return Value:       the char the passed integer represents
**  Pre-Conditions:     the input is an integer
**  Post-Conditions:    returned the character the decimal represents
*/
char i_to_a(int decimal)
{
	//char character = char(decimal);
	//return character;
	return static_cast<char>(decimal);
}

int main()
{
	char character;
	int decimal;
	std::cout << "a_to_i:" << std::endl << "Give a character to be converted: ";
	std::cin >> character;
	std::cout << character << " ==> " << a_to_i(character) << std::endl;
	std::cout << "i_to_a:" << std::endl << "Give an integer to be converted:  ";
	std::cin >> decimal;
	std::cout << decimal << " ==> " << i_to_a(decimal) << std::endl;
	return 0;
}
