/*
 * This program should compute the average and maximum age of all of the
 * people in a TSV data file whose lines each look like this:
 *
 *   LAST_NAME  FIRST_NAME  ID AGE
 *
 * Once compiled, you can run this program like so:
 *   ./debugging-3 data.tsv
 */

#include <iostream>
#include <fstream>
#include <string>

struct person
{
    std::string last_name;
    std::string first_name;
    std::string id;
    int age;
};


/*
 * This function counts and returns the number of entries in a TSV file.  The
 * number of entries is counted as the number of non-empty lines.
 *
 * Hint: there shouldn't be any bugs in this function.
 */
int count_tsv_file_entries(std::ifstream & infile)
{
    std::string line;
    int count = 0;

    // Make sure the file cursor is at the beginning and then count the lines.
    infile.seekg(0);

    do
    {
        getline(infile, line);

        if (line.length() > 0)
        {
            count++;
        }
    }
    while (!infile.eof());

    // Make sure the file's ready to read with the cursor at the beginning.
    infile.clear();
    infile.seekg(0);
    return count;
}


/*
 * This function reads people from a specified data file (with TSV format as
 * described in the file header) into an array of person structs and returns
 * the number of people read.
 */
int read_people(char * filename, struct person *& people)
{
    std::ifstream infile(filename);
    int i = 0, n = count_tsv_file_entries(infile);
    struct person new_person;
    people = new struct person[n];

    while (i < n && !infile.eof())
    {
        infile >> new_person.last_name >> new_person.first_name >> new_person.id
               >> new_person.age;
        people[i++] = new_person;
    }

    return n;
}


/*
 * This function computes and returns the average age of all of the people in
 * an array of person structs.
 */
float compute_avg_age(struct person * people, int n)
{
    float avg = 0;

    for (int i = 0; i < n; i++)
    {
        avg += people[i].age;
    }

    return avg / n;
}


/*
 * This function computes and returns the maximum age of all of the people in
 * an array of person structs.
 */
int compute_max_age(struct person * people, int n)
{
    int max = 0;

    for (int i = 0; i < n; i++)
    {
        if (max < people[i].age)
        {
            max = people[i].age;
        }
    }

    return max;
}


int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: must specify a data file."
                  << std::endl << std::endl;
        std::cerr << "usage: " << argv[0] << " <data_file>" << std::endl;
        return 1;
    }

    struct person * people;

    int n = read_people(argv[1], people);

    float avg_age = compute_avg_age(people, n);

    int max_age = compute_max_age(people, n);

    std::cout << "The average age of the " << n << " people is: " << avg_age
              << std::endl;

    std::cout << "The maximum age of the " << n << " people is: " << max_age
              << std::endl;

    delete[] people;
}
