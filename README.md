# PROJECT_MAZE_AND_CAVE_CPP
The App allows render on the screen the mazes and the caves loaded from the files or generated (max size 50x50). Also it allows render the  maze solving way between two given points and automated generation using a cellular automaton.

_**This App is developed together with @iitrukha1989 and .**_

My actual work in this project consists of the following matters:
- generation of the maze according to Eller's algorithm, 
- solving the maze (wave algorithm of finding the shortes).

### How to Compile the App


### Work with Mazes
There are two tabs in the Apps - **MAZE** and **CAVE**. After the App is opened, you can see the **MAZE** window:

![Alt text](/screenshots/maze_window.jpg "Maze window")

Here you can:
- load the maze from ****.txt file*** (file must be formatted by the certain way, for example, see the folder ***examples***)

![Alt text](/screenshots/open_maze.jpg "Load maze")

- generate the ideal maze, inputing before the rows and columns size (*** The maximum size - 50x50)

![Alt text](/screenshots/generate_maze.jpg "Generate maze")

- find the shortest way between the starting and ending points (or one of the possible ways if maze has loops, or nothing if maze has the isolated area)

![Alt text](/screenshots/solve_maze.jpg "Solve maze")
![Alt text](/screenshots/solve_maze_loop.jpg "Solve maze loop")
![Alt text](/screenshots/solve_maze_isolated.jpg "Solve maze isolated")

- save the genetated ideal maze in *.txt file

![Alt text](/screenshots/Save_maze.jpg "Save maze")



