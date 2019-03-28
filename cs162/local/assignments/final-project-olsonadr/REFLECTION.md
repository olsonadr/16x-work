# Reflection Document



## Important Note

  - Please read my modified README before grading my assignment!



## What decisions or assumptions did you make about how to design your program?

  - My largest assumptions about this design came down to where the brunt of the logic would take place. I wanted the Maze and MazeLevel to be as simple as possible so they could be infinitely reused with any MazePeople, and that’s why I made it so you added pointers to them rather than each having their own MazePeople. Similarly, I wanted to avoid naming specific types of MazePeople to be stored in each Level, so that I could reuse it later. Because of this, I put most of the logic of the actually game loop into a Game class, which I assumed would be okay. To handle special inputs that weren’t necessarily a movement in a direction (because each Level nor the Maze know anything about programming skills or rounds appeased), I decided that each MazeLevel could handle the moves of WASD for themselves because any MazePerson could move or return a space to signify no movement. If the character returned was anything other than WASD or a space, though, my Maze class returns a vector filled with these characters to the Game class so it can handle them (like using a programming skill or going up the ladder). I assume this is fine. I did add a type variable to the MazePerson class but didn’t want to use it for any normal logic, so I just used it for searching for collisions of TAs and the Student and the Instructor and the Student to make life easier and because I thought it was an interesting algorithm to code.



## What was your test plan for your program?

  - For map loading, my plan basically came down to trying to not designate a map file, designate a file that doesn’t exist, designate an incorrectly formatted file, and designate a correctly formatted, existing file. For the main game loop the main things to test were the intersection of the player and the tas as well as the instructor; the player movement and collision with the walls; and the effect of programming skills. For the first, once it was implemented, I would disable the ability of TAs to move and tried walking into the areas that should be deadly. I should be reset to the beginning of the current level stripped of all skills. Similarly, if I walk up to the Instructor I should, if I have 3 or more skills, win the game (I never did implement a nice game over screen), and if I have fewer than 3, lose the game, being reset back to the beginning of the maze. I would test skills by using one and trying to walk into a stationary TA, which shouldn’t do anything. For general movement, walking toward an open space should let me move that way but moving into a wall shouldn’t do anything (and should count as a wasted turn). I didn’t want to waste their turn if they hit a key that isn’t accounted for by the game, so I only commit the movements of the MazePeople if the Player submitted an expected input.



## How did your testing work out? What bugs did you uncover through testing? How did you fix those bugs?

  - The first thing that jumped out at me is that sometimes it would seem like you maybe shouldn’t have been captured, because I checked for intersections with TAs and the Instructor before I redisplayed the maze and returned from within those conditions, so I just added lines to redisplay before returning in each of those conditions. Initially I was having issues with winning / losing weirdly early on the final level, and I realized that I had passed the wrong values in and was trying to check to see if the instructor and any TAs were within range of each other rather than with the player. On top of this, I forgot to reset the number of skills to zero on an instructor reset initially.



## What problems or obstacles did you run into while you were developing your program? How did you resolve these?

  - I had pretty few issues during programming except for the fact that I got the entirety of the game working well and started to work on implementing a fun UI, but realized quickly that it was taking too much time and I had to focus on other final projects, so I had to abandon that. Similarly, my game_turn() function in Game is really messy and I would have liked to separate those out into sub-functions, but I just don’t have time. The same goes for comments. I would have liked to do more and I’ve been pretty consistent in style and quantity this term, but I just don’t have time for it anymore.



## What resources were useful to you in solving problems you ran into? Were there helpful websites or Stack Overflow posts? What help did you get from the TAs and/or the Instructor? Were specific parts of the course notes helpful?

  - I actually didn’t look anything up for this assignment nor did I talk to any TAs or the Instructor for it. My TA was super helpful through the development of my UI library (which I’m in the process of rewriting currently to make it vastly more efficient), but, for this assignment, it was just a matter of applying what y’all have already taught me.
