Lab Exercise #7
===============

This is the repo for CS 162's Lab #6.  You will commit your source code files into this repository for the TAs to check off.  The description of the lab exercise is below and can also be found here:

https://docs.google.com/document/d/1IxW2MbbE0xWOerRcQoi3YYn_5TsmdwSc9v_061OosZk/edit?usp=sharing

In this lab, you’ll practice debugging using gdb.

## Step 1: Clone the git repository for this lab

We’re going to use git and GitHub Classroom again for this lab.  Just like you did for the previous lab exercises, use git clone to download your repository onto your development machine using the clone URL from your repo on GitHub:
```
git clone REPO_URL
```

## Step 2: TA demo

Before you start working on using gdb yourself, your TAs will demonstrate how to use gdb to debug a buggy program, `debugging-demo.cpp`.  Watch carefully as they explain how to run the program with gdb and how to use gdb’s various commands, and follow along yourself in the source code as they debug.

Some important commands to watch for during the demo (links to command documentation are included):
  * [`run`](https://sourceware.org/gdb/onlinedocs/gdb/Starting.html#index-run-113) – starts your program from the beginning.  Command line arguments to your program can be specified with the `run` command.
  * [`break`](https://sourceware.org/gdb/onlinedocs/gdb/Set-Breaks.html#index-break-229) – tells gdb to pause the execution of your program once it reaches a specified line in your source code.  This is called setting a **breakpoint**.
  * [`list`](https://sourceware.org/gdb/onlinedocs/gdb/List.html#index-list-527) – prints out the lines of source code near the one currently being executed or near a specified location.
  * [`print`](https://sourceware.org/gdb/onlinedocs/gdb/Data.html#index-print-586) – prints out the the value stored in a specified variable, etc.
  * [`step`](https://sourceware.org/gdb/onlinedocs/gdb/Continuing-and-Stepping.html#index-step-339) – tells gdb to execute the very next line of code when it’s paused at a breakpoint.  If the next line of code is inside a function call, the `step` command enters that function.
  * [`next`](https://sourceware.org/gdb/onlinedocs/gdb/Continuing-and-Stepping.html#index-next-341) – a lot like the `step` command; tells gdb to execute the very next line of code when it’s paused at a breakpoint.  However, if the next line of code is inside a function call, the `next` command runs that function without entering into it.
  * [`watch`](https://sourceware.org/gdb/onlinedocs/gdb/Set-Watchpoints.html#index-watch-262) – tells gdb to pause whenever the value of a specified variable changes and to print out the change in that variable’s value.  This is called setting a **watchpoint**.
  * [`continue`](https://sourceware.org/gdb/onlinedocs/gdb/Continuing-and-Stepping.html#index-continue-336) – tells gdb to resume normal execution of the program from the line of code where it’s currently stopped until the next breakpoint, watchpoint, etc.
  * [`backtrace`](https://sourceware.org/gdb/onlinedocs/gdb/Backtrace.html#index-bt-_0040r_007b_0028_0040code_007bbacktrace_007d_0029_007d-496) – prints a backtrace, which is the sequence of function calls (called **frames**) that brought the program to the current line of code being executed.

## Step 3: Start using gdb on your own

Now it’s your turn to start using gdb.  Remember, the very first thing you need to do to start to use gdb is to make sure the code you want to debug is compiled with debugging symbols.  To do this, add the `-g` option to all of the g++ commands in the makefile in your git repository for the lab.

## Step 4: Fix `debugging-1.cpp`

Now that you can compile your programs with debugging symbols, it’s time to start debugging.  Take a look at the source code of `debugging-1.cpp`.  Compile and run the program to see what happens.

There’s obviously a bug in the program, since it ends with a segmentation fault.  In this case, the bug is straightforward enough that you might be able to spot it just by looking at the source code, but for now, start gdb, and run `debugging-1` in it.  Use the commands you saw the TAs demo to figure out where and what the bug in this program is.  Once you know what the bug is, fix it, and commit your changes into your git repo, then push them to GitHub.

## Step 5: Document your debugging process

Create a new text file `debugging-1.txt`.  In this file, write out a description of how you used gdb to identify the bug in `debugging-1.cpp`, as well as a description of what the bug actually was and how you fixed it.  Add and commit this file to your git repo, and push it to GitHub when you’re done.

## Step 6: Fix `debugging-2.cpp`

Take a look at the source code of `debugging-2.cpp`.  This program has a few slightly more subtle bugs in it.  Compile and run the program, passing different values of `n`, to see how the program behaves.

Run `debugging-2` in gdb, and use the commands you saw the TAs demo to figure out where and what the bugs in this program are.  Importantly, because the code in `debugging-2.cpp` uses the `Dynarray` class, which is defined elsewhere, you might have to track bugs through multiple files to fix them.  Once you know what the bugs are, fix them, and commit your changes into your git repo, then push them to GitHub.

## Step 7: Document your debugging process

Create a new text file `debugging-2.txt`.  In this file, write out a description of how you used gdb to identify the bugs in `debugging-2.cpp`, as well as a description of what the bugs actually were and how you fixed them.  Add and commit this file to your git repo, and push it to GitHub when you’re done.

## Step 8: Fix `debugging-3.cpp`

Finally, take a look at the source code of `debugging-3.cpp`.  This program has a few bugs in it.  Compile and run the program with the provided data file, `data.tsv`, to see how the program behaves.

Again, use gdb to run and investigate `debugging-3`.  Try to fix all of the bugs in the program.  For reference, the true average age of all 8 people in `data.tsv` is 29, and the true maximum age is 58.

## Step 9: Document your debugging process

Create a new text file `debugging-3.txt`.  In this file, write out a description of how you used gdb to identify the bugs in `debugging-3.cpp`, as well as a description of what the bugs actually were and how you fixed them.  Add and commit this file to your git repo, and push it to GitHub when you’re done.

## Grading Criteria

That’s it!  After you’re done with your lab, make sure you get it checked off by your TA so that you get points for it.  If you don’t get your work checked off, you’ll receive a zero for the lab, and we won’t be able to change your grade, since we’ll have no way to know whether or not you were at the lab.

This lab is worth 10 points total.  Here’s the breakdown:
  * 2 point: debugged and fixed `debugging-1.cpp`
  * 1 point: wrote description of debugging `debugging-1.cpp` in `debugging-1.txt`
  * 2 points: debugged and fixed `debugging-2.cpp`
  * 1 point: wrote description of debugging `debugging-2.cpp` in `debugging-2.txt`
  * 3 points: debugged and fixed `debugging-3.cpp`
  * 1 point: wrote description of debugging `debugging-3.cpp` in `debugging-3.txt`
