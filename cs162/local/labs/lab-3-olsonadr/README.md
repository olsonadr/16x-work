Lab Exercise #3
===============

In this lab, we will explore reading and writing files using C++ file I/O operations.

## Step 1: Clone the git repository for this lab

We’re going to use git and GitHub Classroom again for this lab.  Just like you did for Lab Exercise #1, use git clone to download your repository onto your development machine using the clone URL from your repo on GitHub:
```
git clone REPO_URL
```

## Step 2: Write a program to count letters in a file

Your git repo for this lab comes with a file called `testfile.txt`.  Take a look at this file.  Your first job is to write a program to read `testfile.txt` and count the number of times each letter occurs in the file, disregarding case (i.e. 'A' and 'a' count the same) and ignoring punctuation or other non-letter characters.  That means there are 26 characters you need to count.

Your program should accept the name of the file to process as its only command line argument.  That is, if your executable program is called `count_letters`, you would run it like this:
```
./count_letters testfile.txt
```

Your program should work by opening the file to read as an `std::std::ifstream`.  Once you have the file opened as an `std::ifstream`, you should pass the `std::ifstream` to a function like this:
```c++
void count_letters(std::ifstream&, int*);
```

This function should do the work of actually reading through the `std::ifstream` that represents your opened file and counting the letters there, storing the counts in a pre-allocated array of integers that’s passed in.

Think carefully about how you want to design this function.  There’s a way to implement it in such a way that you only have to make one pass reading through the file and don’t have to allocate any additional memory (beyond the `std::ifstream` and the array of `int`s).  See if you can figure out how to do that.  After you’ve worked on this problem for a little while, your TAs will stop you so they can compare some of your approaches to go over their pros and cons.

Here’s some more documentation that will help you get going with `std::ifstream`:
  * [`std::ifstream` constructor](http://www.cplusplus.com/reference/fstream/ifstream/ifstream/)
  * [C++ Basic file I/O](http://www.learncpp.com/cpp-tutorial/186-basic-file-io/)

Also remember that, once you have a file open, `std::ifstream` works pretty much exactly like `std::cin`, which you should be familiar with.  The main difference is that instead of reading input from the user in the terminal, `std::ifstream` reads input from a file.

## Step 3: Commit your work to your git repo and push it to GitHub

Once you’re happy with your `count_letters()` function, commit your work into your git repo and push it back to GitHub.  Make sure you check your repo on github.com to verify that your code was successfully pushed there.  This is how the TAs will check off your work.

## Step 4: Save your letter counts to a new file

Now, add new functionality to your program to take the letter counts you computed earlier and write them into a new file as tab-separated values.  Your program should take the name of the file to which to write the letter counts as its second command line argument, e.g.:
```
./count_letters testfile.txt counts.tsv
```

To add this functionality to your program, you should open the file to which to write as an `std::ofstream`.  Once you have the `std::ofstream`, you should pass it along with the letter counts you computed to a new function that actually writes the counts to the file:
```c++
void write_counts(std::ofstream&, int*);
```

This function should do the work of actually writing the letter counts to the file represented by the `std::ofstream`.  In particular, the counts should be written in a format like this, with a letter and its count on a single line, separated by a tab (these are not the actual counts, they’re just an example):
```
a	13
b	3
c	20
d	16
e	31
...
```

Here’s some additional documentation on `std::ofstream` that may be useful:
  * [`std::ofstream` constructor](http://www.cplusplus.com/reference/fstream/ofstream/ofstream/)

Again, remember that once you have a file opened, `std::ofstream` works pretty much exactly like `std::cout`, the main difference being that `std::ofstream` writes to a file instead of to the console.

## Step 5: Commit your work to your git repo and push it to GitHub

Once you’re happy with your `write_counts()` function, commit your work into your git repo and push it back to GitHub.  Make sure you check your repo on github.com to verify that your code was successfully pushed there.  This is how the TAs will check off your work.

## Grading Criteria

That’s it!  After you’re done with your lab, make sure you get it checked off by your TA so that you get points for it.  If you don’t get your work checked off, you’ll receive a zero for the lab, and we won’t be able to change your grade, since we’ll have no way to know whether or not you were at the lab.

This lab is worth 10 points total.  Here’s the breakdown:

  * 7 points: your `count_letters()` function works correctly and is committed and pushed to your repository on GitHub (i.e. everything through Step 3 is done).

  * 3 points: your `write_counts()` function works correctly and is committed and pushed to your repository on GitHub (i.e. everything through Step 5 is done).
