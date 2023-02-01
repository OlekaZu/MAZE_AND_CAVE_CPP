# PROJECT_MAZE_AND_CAVE_CPP
The App allows render on the screen the mazes and the caves loaded from the files or generated (max size 50x50). Also it allows render the  maze solving way between two given points and automated generation using a cellular automaton.

_**This App is developed together with @iitrukha1989 and .**_

My actual work in this project consists of the following matters:
- generation of the maze according to Eller's algorithm, 
- solving the maze (wave algorithm of finding the shortes).

### How to Compile the App
#### MacOS, Linux
```bash
qmake -o Makefile MazeCave/Maze.pro
make -f Makefile -j1 
rm -rf moc_* ui_* .qmake.stash qrc_rsc.cpp Makefile build*
```
#### Windows
```bash
mkdir Install
qmake.exe -o Install/Makefile MazeCave/Maze.pro
cd Install
mingw32-make.exe -f Makefile -j20
ls | grep -v release | xargs rm -rfv
```

### Work with Mazes
There are two tabs in the Apps - **MAZE** and **CAVE**. After the App is opened, you can see the **MAZE** window:

![Alt text](/screenshots/maze_window.jpg "Maze window")

Here you can:
- load the maze from ****.txt file*** (file must be formatted by the certain way, for example, see the folder ***examples***)

![Alt text](/screenshots/open_maze.jpg "Load maze")

- generate the ideal maze, inputing the rows and columns size (***The maximum size - 50x50***)

![Alt text](/screenshots/generate_ideal_maze.jpg "Generate maze")

- find the shortest way between the starting and ending points (or one of the possible ways if maze has loops, or nothing if maze has the isolated area)

![Alt text](/screenshots/solve_maze.jpg "Solve maze")

![Alt text](/screenshots/solve_maze_loop.jpg "Solve maze loop")

![Alt text](/screenshots/solve_maze_isolated.jpg "Solve maze isolated")

- save the genetated ideal maze in *.txt file

![Alt text](/screenshots/save_maze.jpg "Save maze")

### Work with Caves
Switched on **CAVE** tab, you can see this:

![Alt text](/screenshots/cave_window.jpg "Cave window")

Here you can:
- load the cave from ****.txt file*** (file must be formatted by the certain way, for example, see the folder ***examples***)

![Alt text](/screenshots/open_cave.jpg "Load cave")

- generate the cave, inputing the rows and columns size (***The maximum size - 50x50***), the *birth* and *death* limits,  as well as the chance for the starting initialization of the cell (each from 0 to 7).

If *live* cells (grey color cell)  are surrounded by *live* cells, the number of which is less than the *death* limit, they *die*. In the same way, if *dead* cells (white color cell) are next to *live* cells, the number of which is greater than the *birth* limit, they become *live*.

![Alt text](/screenshots/generate_cave.jpg "Generate cave")

- continue generating caves using the **Next Step** button or the **Auto Build** button (in this case you need to choose frequence in msec)

![Alt text](/screenshots/next_step_cave.jpg "Next step cave")

![Alt text](/screenshots/auto_cave.jpg "Auto cave")

- in auto mode you can stop the generation by the **Stop Build** button


