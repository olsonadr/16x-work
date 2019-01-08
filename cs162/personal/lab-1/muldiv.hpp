#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

void print_tables(struct muldiv_entry **, int);
struct muldiv_entry ** generate_tables(int);
void free_tables(struct muldiv_entry **, int);

struct muldiv_entry
{
	int mul;
	float div;
};
