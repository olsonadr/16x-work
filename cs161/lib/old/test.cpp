#include <iostream>
#include "help.h"

using std::cout;
using std::cin;
using std::endl;
//using HelperLib::print;
//using HelperLib::input;
using namespace HelperLib;

int main()
{
	print("Ahh", 1, "WOW", 'c', 100.5);
	input("Input me daddy: ", 4);
	cout << getIntInput("Input int here nerd --> ", 2) << endl;
	cout << getFloatInput("Input float here nerd -->", 1) << endl;
	cout << toUpper(input("String with lowercase stuff >> ", 0)) << endl;
	cout << toLower(input("String with uppercase stuff >> ", 1)) << endl;
	cout << "contains(\"yeet\", \"ee\"): " << contains("yeet","ee") << endl;
	cout << "equalsF(50.5,50.2,.5): " << equalsF(50.5, 50.2, .5) << endl;
	cout << "Is 5 odd? " << isOdd(5) << endl;
	cout << "Is 8 odd? " << isOdd(8) << endl;
	cout << "Is 5 even? " << isEven(5) << endl;
	cout << "Is 8 even? " << isEven(8) << endl;
}
