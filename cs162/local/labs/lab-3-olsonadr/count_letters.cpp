// Libraries
#include <iostream>
#include <fstream>


// Prototypes
int open_files(int, char **, std::ifstream &, std::ofstream &);
void count_letters(std::ifstream &, int *);
void write_out(std::ofstream &, int *, int);


// Functions
/*
**  Function:		main
**  Description:	Calls functions to initialize values, read the
**			    data file, and count the letters.
**  Parameters:		int argc:
**			    Count of arguments passed on program-
**			    execution. Holds 1 for no additional
**			    arguments, 2+ otherwise.
**			char * argv[]:
**			    Array of the C-style strings representing
**			    all arguments passed on execution of the
**			    program. argv[0] is the name of the file.
**  Return Value:	Returns 0 on succesful program execution,
**			    1 for an argument error, 2 for a file
**			    read error, etc.
**  Pre-Conditions:	If an argument is provided, it points to an
**			    appropriately formatted data file.
**  Post-Conditions:	User is extremely satisfied with the quality
**			    of the program and my abilities.
*/
int main(
    int argc,
    char ** argv)
{
    // Vars
    int error = 0;

    // Open files
    std::ifstream data_file;
    std::ofstream out_file;
    error = open_files(
                argc, argv,
                data_file,
                out_file);

    if (error > 0)
    {
        return error;
    }

    // Count Letters
    int num_letters = 26;
    int * letter_counts = new int[num_letters]; /* Each element 0 initialized */
    count_letters(
        data_file,
        letter_counts);

    // Output
    write_out(
        out_file,
        letter_counts,
        num_letters);

    // Cleanup
    data_file.close();
    delete[] letter_counts;
    return 0;
}


/*
** Function:		open_file
** Description:		Opens the file the user specified in their command-
**			    argument. Returns error codes otherwise.
** Parameters:		int argc:
**			    Number of arguments passed.
**			char * argv[]:
**			    Array of arguments passed, starting with program
**			    filename at argv[0].
**			std::ifstream data_file:
**			    The ifstream to open the file into.
** Return Value:	Returns 0 for successful execution, 1 for argument
**			    error, 2 for a file read error, etc.
** Pre-Conditions:	Files are unopened.
** Post-Conditions:	Files have been opened.
*/
int open_files(
    int argc,
    char * argv[],
    std::ifstream & data_file,
    std::ofstream & out_file)
{
    // Open Files
    if (argc < 3)
    {
        std::cout << "**ERROR! No path to each file provided.**"
                  << std::endl;
        return 1;
    }

    data_file.open(argv[1]);
    out_file.open(argv[2]);

    if (data_file.fail()
            || out_file.fail())
    {
        std::cout << "**ERROR! Invalid path to file provided.**"
                  << std::endl;
        return 1;
    }
    else if (!data_file.is_open()
             || !out_file.is_open())
    {
        std::cout << "**ERROR! File reading error, try again.**"
                  << std::endl;
        return 2;
    }

    return 0;
}


/*
** Function:		count_letters
** Description:		Modifies the values of the passed int array,
**			    such that each index points to the count
**			    of each letter in the file (a/A - z/Z).
** Parameters:		std::ifstream & data_file:
**			    The data file to read from.
**			int * letter_counts:
**			    The pre-allocated array of letter counts.
** Pre-Conditions:	data_file is at beginning of section of file
**			    desired to be read, letter_counts is at
**			    correct initial values.
** Post-Conditions:	data_file is at end of file, letter_counts is
**			    populated with counts of alpha chars in
**			    desired section.
*/
void count_letters(
    std::ifstream & data_file,
    int * letter_counts)
{
    bool keep_going = !data_file.eof();
    int curr_char;

    while (keep_going)
    {
        curr_char = data_file.get();

        if (curr_char >= 'A'
                && curr_char <= 'Z')
        {
            letter_counts[curr_char - 'A']++;
        }
        else if (curr_char >= 'a'
                 && curr_char <= 'z')
        {
            letter_counts[curr_char - 'a']++;
        }

        keep_going = !data_file.eof();
    }
}


void write_out(
    std::ofstream & out_file,
    int * letter_counts,
    int num_letters)
{
    out_file << "Occurences of Alpha Characters:"
             << std::endl
             << " Chars | Count"
             << std::endl
             << "*------*------*"
             << std::endl;

    for (int i = 0; i < num_letters; i++)
    {
        out_file << "  "
                 << char(i + 65)
                 << "/"
                 << char(i + 97)
                 << "  |  "
                 << letter_counts[i]
                 << std::endl;
    }

    out_file << "*------*------*"
             << std::endl;
}
