# Nick Olson's Final Project

## Notes
- *BECAUSE OF HOW MY UI SYSTEM WORKS, YOU MUST NOT BE IN A MAXIMIZED WINDOW WHEN LAUNCHING THE PROGRAM FOR IT TO RESIZE YOUR TERMINAL. IT IS TESTED USING A POPPED OUT PUTTY TERMINAL, AN SSH CONNECTION FROM THE STOCK WINDOWS CMD, AND ON A LINUX TERMINAL (GNOME-TERMINAL) BOTH LOCALLY AND ON THE SSH SERVER (FLIP AND ACCESS)*

- You can use the command `vim -S doc/sessions/Session.vim` to open all my source code organized into vim tabs containing each class’s source code and header file, as well as my makefile, drafting document, readme, reflection, etc. If you have your mouse disabled you can enable it by using `:set mouse=1` in vim and then click between tabs. You can also use `<g>, <t>` (hit the ‘g’ key then hit the ‘t’ key) in vim normal mode to go to the next tab. Without a mouse, you can use `<ctrl>+<w>, <h|j|k|l>` (control and w together then a vim direction key) in normal mode to move your cursor between splits.

- This project was intended to use a personal UI building library for both the menu system and game. This library is coded by me and is hosted on its own github repo, which is included as a git submodule cloned into this project’s `lib/cpp_panels` directory. I used the submodule so you could see the source code so you could grade it appropriately. To make it as easy as possible to compile this composite project, I added a check to the all target of my projects makefile that should call the `git submodule init` and `git submodule update` commands automatically when making to hopefully clone all the library’s code. It may ask for a github login but it hopefully won’t as the library is public. You can find the library at this url:
  - https://github.com/olsonadr/cpp_panels

- Feel free to check out the page if you need to. I didn’t end up adding the UI system to the game-loop because I have too many other classes to make final projects for, but the menu is hopefully appreciated. I also added a `maps` directory to the project root which holds all map files, as my program does not use the command line argument to designate the map to load. In the ‘load maze’ option of the main menu you can choose any file placed into the `maps` directory to parse as a maze and play it. I added two example other mazes for a template. The `maze.txt` file is the original given for the assignment.

- The only other important note is that this project is structured such that temporary .o files are added to the `build` directory when made, and the executable file `escape_cs` is added to the `bin` directory. I accounted for different ways of running the executable, so free to run it from the root directory using `./bin/escape_cs` or from within the bin directory using `./escape_cs`.


The following is the Grading Criteria section copied from the original README.md for your convenience:

## Grading criteria

Your program **MUST** compile and run on `flip.engr.oregonstate.edu`, so make sure you have tested your work there before you make your final submission, since a program that compiles and runs in one environment may not compile and run in another.  **Assignments that do not compile on `flip` will receive a grade of 0.**  If you do not have an ENGR account, you can create one at https://teach.engr.oregonstate.edu/.

This assignment is worth 100 points total:
  * 10 points: your code is appropriately commented and uses consistent and appropriate style
  * 15 points: your `REFLECTION.txt` document thoughtfully explains your work on your project
  * 15 points: your program correctly reads maze levels from a maze configuration file and creates corresponding `MazeLevel` objects, including error checking on the input file
  * 10 points: the `Wall` and `OpenSpace` classes are correctly implemented and derive from the (correctly implemented) `MazeLocation` class
  * 10 points: the `IntrepidStudent`, `TA`, and `Instructor` classes are correctly implemented and derive from the (correctly implemented) `MazePerson` class
  * 10 points: objects of the `IntrepidStudent`, `TA`, and `Instructor` classes correctly move around the maze
  * 5 points: climbing a ladder brings the Intrepid Student to the next level in the maze
  * 5 points: the Intrepid Student picks up a Programming Skill when moving into a space containing one, while TAs do not affect Programming Skills
  * 5 points: if a TA enters a space adjacent to the Intrepid Student and the TA is not appeased, the level is reset, and the Intrepid Student starts from the beginning of the level after losing all Programming Skills
  * 5 points: demonstrating a Programming Skill appeases the TAs on the current level for 10 turns
  * 5 points: if the Intrepid Student reaches the Instructor and holds at least 3 Programming Skills, they are allowed to escape from the maze with a passing grade; otherwise they must repeat the entire maze from the beginning
  * 5 points: all dynamically allocated memory is correctly freed (no memory leaks)

Segmentation faults and other similar errors will result in a 20 point deduction.  **Remember, you won't demo this project for a grade.**
