//
//  main.cpp
//  Rat-in-a-Maze
//
//  Created by Ethan Chan on 2021/10/18.
//  Copyright © 2021 Ethan Chan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <vector>
#include <string>
using namespace std;


const int SIZE = 17;

struct position  // position format for each cell
{
    int x, y, dir;  // row, column, direction (enum directions)
};

struct offsets
{
    int x, y;
};

vector<vector<bool> > create_maze(string filename);
void print(const vector<vector<bool> > array);

int main()
{
    string filename;
    vector<vector<bool> > maze;
    vector<vector<bool> > visited(SIZE, vector<bool> (SIZE)); // visited cells
    stack<position> path;  // escape path from start to exit
    enum directions {E, S, N, W};
    const vector<offsets> move = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};  // position change
                                                                      // in the four directions
                                                                      // E, S, N, W
    /*
     * User input name of file that contains the maze problem.
     * The maze would be converted to a 2D vector then printed to console.
     */
    cout << "enter filename : ";
    cin >> filename;
    maze = create_maze(filename);
    print(maze);

    /*
     * Enter program flow structure.
     * Exit when user input = (-1, -1).
     */
    while (true)
    {
        /*
         * User input starting position of the rat and exit position in the maze.
         */
        int x_start, y_start, x_exit, y_exit;
        cout << "enter start position : ";
        cin >> x_start >> y_start;
        if ((x_start == -1) && (y_start == -1)) { break; }  // enter (-1, -1) to exit
        cout << "enter exit position : ";
        cin >> x_exit >> y_exit;
        if ((x_exit == -1) && (y_exit == -1)) { break; }

        // Initialize data structures.
        for (auto &row : visited) {
            fill(row.begin(), row.end(), false);
        }
        while (!path.empty())
        {
            path.pop();
        }
        int step_count = 0;

        // Initialize starting point.
        position current = {x_start, y_start, E};
        path.push(current);
        visited[x_start][y_start] = true;

        /*
         * Maze escape algorithm.
         * Will continually search for an unvisited cell torwards the exit until:
         * a) the exit is reached
         * b) all cells were visited,
         *    i.e. the rat has backtracked to its starting position.
         */
        while (!path.empty()) // while there are still unvisited cells
        {
            // Pop the foremost cell on the solution path and explore its neighbors.
            current = path.top();
            path.pop();
            cout << step_count++ << ":" << current.x << "," << current.y << endl;

            // Explore cells in the order of direction: E, S, N, W.
            // Will continuously loop forward if an unvisited cell was found.
            while (current.dir <= W)
            {
                // Explore the neighbor cell in the direction.
                int x_next = current.x + move[current.dir].x;
                int y_next = current.y + move[current.dir].y;

                // The neighbor cell is the exit.
                if ((x_next == x_exit) && (y_next == y_exit))
                {
                    cout << step_count << ":" << x_next << "," << y_next << endl;
                    cout << "successfully escaped!!" << endl;
                    goto endProblem;
                }

                // The neighbor cell has not been visited, move to that cell.
                if ((!maze[x_next][y_next]) && (!visited[x_next][y_next]))
                {
                    current.dir += 1;  // record next direction to explore should the rat backtrack
                    path.push(current);  // write current position to path

                    // Move rat to the neighbor cell.
                    current.x = x_next;
                    current.y = y_next;
                    current.dir = E;
                    visited[x_next][y_next] = true;
                    cout << step_count++ << ":" << current.x << "," << current.y << endl;
                }

                // The neighbor cell has been visited or is a wall.
                else current.dir++;  // turn to the next direction
            }
            // The current cell is a dead end.
        }

        // All cells were visited but could not reach the exit.
        cout << "Failed to escape." << endl;
        endProblem: ;
    }
    cout << "end the code.";

    return 0;
}

/*
 * Read maze text from file and convert it to a 2D vector.
 * The vector dimensions is SIZE * SIZE, with false(0) being walkable cells
 * and true(1) representing walls.
 */
vector<vector<bool> > create_maze(string filename)
{
    vector<vector<bool> > maze(SIZE);
    string line;
    int row = 0;

    // Read file.
    ifstream inFile(filename, ios::in);
    if (!inFile)
    {
        cerr << "Failed to open " << filename << endl;
        exit(1);  // exit program if failed to read file
    }

    // Write maze layout into vector.
    while (getline(inFile, line))
    {
        for (int i = 0; i < SIZE; ++i)
        {
            maze.at(row).push_back(line.at(i) - '0');  // ASCII value subtraction = convert char to int
        }
        row++;
    }

    return maze;
}

/*
 * Print 2D vector to console.
 */
void print(const vector<vector<bool> > array)
{
    for (auto row : array)
    {
        for (auto elem : row)
        {
            cout << elem;
        }
        cout << endl;
    }
}
