### Intro:

This is a repository started to hold a representative sample of the algorithm implementations I've written while originally teaching
myself Algorithms and through Graduate school.  All code is either based on problems avaliable online or individual projects.  Compiled code is left in the fully compiled
state as code is meant to be demonstrative.

#### Here are some implementations of fundamental CS algorithms and concepts in C++

* [A-Star Search](https://github.com/tehwentzel/Algorithms/tree/master/A-Star%20Search) Is an implementation of the A* Search algorithm for solving the 8-Puzzle in C++.  It starts with a "board" layout
in the "test.exe" file, which specifies the initial size of the puzzle (3 for a 3x3 puzzle) as well as the state.  It implements a "Board" class that uses an A* search based on the [Manhattan Distance](https://heuristicswiki.wikispaces.com/Manhattan+Distance)
The output for the file is the board states for the solution in reverse order to the cmd window.

* [C++ Login Interface](https://github.com/tehwentzel/Algorithms/tree/master/C%2B%2B%20Login%20Interface) Explores I/O in C++.
It allows a user to "log in" to a system based on usernames and passwords stored in 'passwort.txt'. When the program exits, 
it should save information for all existing accounts into the file password.txt.  In addition to usernames and passwords, 
every account has an associated e-mail address.  
The program will allow users who are already logged on to change their password or update their e-mail address.  

* [Sorting](https://github.com/tehwentzel/Algorithms/tree/master/Sorting) is an implementation of of a solution to the [Colinear Line Problem](https://introcs.cs.princeton.edu/java/assignments/collinear.html) in C++.
It reads in a text file of several "points", and finds all point that are collinear using a brute-force and sorting based method (using a custom comparator functor and std::stablesort).  The output
is the list of all sets of 4 collinear points in the brute force method, followed by a reduced set of all lines with 4+ collinear points using sorting.

#### Here are some of the more advanced algorithms tested in python, mainly take from recent research papers in robotics-related fields:

* [Distributed Optimization In Smartgrid Pricing](https://github.com/tehwentzel/Algorithms/tree/master/Distributed%20Optimization%20in%20Smartgrid%20Pricing) is code that 
implements 3-4 different methods for smartgrid pricing take from research papers in python.  The writeup contains a more in-depth breakdown of the algorithms
as well as the results of the implemention.

* [Sequenction Action Control](https://github.com/tehwentzel/Algorithms/tree/master/Sequential%20Action%20Control) Implements a method of optimal
control in python.  The algorithm, called [SAC](https://arxiv.org/abs/1708.09347) is done on the cart pendulum problem, where the controller forces a pendulum to be held upright.
