# Rat in a Maze
* contributed by < `詹子毅 F04066028` >
* course: [NCKU Data Structures 2021](http://class-qry.acad.ncku.edu.tw/syllabus/online_display.php?syear=0110&sem=1&co_no=F720300&class_code=2)
* course instructor: Prof. Tseng, Fan-Hsun

## Configuration
* language: C++11
* environment: MacOS Terminal
* compiler: Apple LLVM version 10.0.1 (clang-1001.0.46.4)

## Build
If you are using `clang 3.3` or above, simply run
```
$ make
```
If you are using `gcc 4.8.1` or above, manually enter the command below
```
$ gcc -o main main.cpp -lstdc++
```
Finally, run `main` with
```
$ ./main
```
Make sure `maze.txt` is included in the same directory.

## Program Structure
```javascript    
initialize 2D array MAZE  // user input
initialize stack PATH     // solution path

while user enters a problem
{
    set start & exit position
    push start position into PATH

    while there are still unvisited cells
    {
        pop current position from PATH

        while there is an unexplored neighbor
        {
            if neighbor is the exit
            {
                "Successfully escaped!!"
                // back to first while loop
            }
            if the neighbor is an unvisited cell
            {
                push current position into PATH
                let current position = neighbor position
            }
            else explore next neighbor
        }
        // current cell is a dead end
    }
    "Failed to escape."
}
```