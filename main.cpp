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

struct position
{
    int x, y, dir;
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
    vector<vector<bool> > visited(SIZE, vector<bool> (SIZE)); // visited tiles
    stack<position> path;  // escape path from start to exit
    enum directions {E, S, N, W};
    const vector<offsets> move = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};  // position change
                                                                      // in the four directions
                                                                      // E, S, N, W

    // User input name of file that contains the maze problem.
    // The maze would be converted to a 2D vector then printed to console.
    cout << "enter filename : ";
    cin >> filename;
    maze = create_maze(filename);
    print(maze);

    // Enter program flow structure.
    // Exit when user input = (-1, -1).
    while (true)
    {
        // User input starting position of the rat and exit position in the maze.
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

        // Maze escape algorithm.
        // Will continually search for a possible step torwards the exit until:
        // a) the exit is reached
        // b) all possible steps are exhausted,
        //    i.e. the rat has backtracked to its starting position.
        while (!path.empty()) // while there is still room to backtrack
        {
            // Backtrack one step if no advances are possible. (except for the 1st step)
            current = path.top();
            path.pop();
            cout << step_count++ << ":" << current.x << "," << current.y << endl;

            // Try step directions in the order of E, S, N, W.
            // Will continue to advance if a possible step is found.
            while (current.dir <= W)  // while not all directions are explored
            {
                // Explore the next step in the direction.
                int x_goto = current.x + move[current.dir].x;
                int y_goto = current.y + move[current.dir].y;

                // The next step is the exit.
                if ((x_goto == x_exit) && (y_goto == y_exit))
                {
                    cout << step_count << ":" << x_goto << "," << y_goto << endl;
                    cout << "successfully escaped!!" << endl;
                    goto endProblem;
                }

                // The next step has not been visited, i.e. it is a possible step.
                if ((!maze[x_goto][y_goto]) && (!visited[x_goto][y_goto]))
                {
                    current.dir += 1;  // record next direction to explore should the rat backtrack
                    path.push(current);  // write current position to path

                    // Move rat to the next step.
                    current.x = x_goto;
                    current.y = y_goto;
                    current.dir = E;
                    visited[x_goto][y_goto] = true;
                    cout << step_count++ << ":" << current.x << "," << current.y << endl;
                }

                // The next step has been visited or is a wall.
                // Move on to the next direction.
                else current.dir++;
            }
        }
        cout << "Failed to escape." << endl;

        endProblem: ;
    }
    cout << "end the code.";

    return 0;
}

// Read maze text from file and convert it to a 2D vector.
// The vector dimensions is SIZE * SIZE, with false(0) being walkable tiles
// and true(1) representing walls.
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

// Print 2D vector to console.
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
