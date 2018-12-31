#include <iostream>
using namespace std;

void get_string(string *);
void set_replace_string(string, string *);
int get_search_replace(char, string, string &);
void heap_me(int **);
void change_heap(int *);
void empty_heap(int *);

int main()
{
	string * input_ref;
	input_ref = new string;
	get_string(input_ref);
	string copy = *input_ref;
	set_replace_string(copy, &copy);
	char character;
	cout << "Supply a character to search for: ";
	cin >> character;
	get_search_replace(character, *input_ref, copy);
	cout << "Original string: " << *input_ref << endl << "New string:" << copy << endl;
	delete input_ref;

	int * pointer;
	int ** pointer_pointer = &pointer;
	heap_me(pointer_pointer);
	cout << "pointer_pointer = " << pointer_pointer << endl;
	cout << "*pointer_pointer = " << *pointer_pointer << endl;
	cout << "**pointer_pointer = " << **pointer_pointer << endl;
	cout << "pointer = " << pointer << endl;
	cout << "*pointer = " << *pointer << endl;
	change_heap(pointer);
	cout << "pointer = " << pointer << endl;
	cout << "*pointer = " << *pointer << endl;
	empty_heap(pointer);
	return 0;
}

void change_heap(int * pointer) {
	*pointer = 200;
}

void heap_me(int ** pointer_pointer) {
	*pointer_pointer = new int(50);
}

void empty_heap(int * pointer_reference) {
	delete pointer_reference;
}

void get_string(string * input)
{
	cout << "Supply a string to play with: ";
	cin >> *input;
}

void set_replace_string(string copy, string * copy_ref)
{
	for (int i = 0; i < copy.length(); i++)
	{
		if (copy[i] != ' ')
		{
			copy[i] = '-';
		}
	}

	*copy_ref = copy;
}

int get_search_replace(char character, string original, string & copy)
{
	int count = 0;

	for (int i = 0; i < original.length(); i++)
	{
		if (original[i] == character)
		{
			copy[i] = character;
			count++;
		}
	}

	return count;
}