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
    vector<vector<bool> > visited(SIZE, vector<bool> (SIZE, false));
    stack<position> path;
    enum directions {E, S, N, W};
    const vector<offsets> move = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};  // E, S, N, W

    cout << "enter filename : ";
    cin >> filename;
    maze = create_maze(filename);
    print(maze);

    int x_start, y_start, x_exit, y_exit, count;
    while (true)
    {
        // user input
        cout << "enter start position : ";
        cin >> x_start >> y_start;
        if ((x_start == -1) && (y_start == -1)) { break; }
        cout << "enter exit position : ";
        cin >> x_exit >> y_exit;
        if ((x_exit == -1) && (y_exit == -1)) { break; }

        // clear data structures
        for (auto &row : visited) {
            fill(row.begin(), row.end(), 0);
        }
        while (!path.empty())
        {
            path.pop();
        }
        count = 0;

        // initialize starting point
        position current = {x_start, y_start, E};
        path.push(current);
        visited[x_start][y_start] = true;

        // algorithm
        while (!path.empty())
        {
            current = path.top();
            path.pop();
            cout << count++ << ":" << current.x << "," << current.y << endl;
            while (current.dir <= W)
            {
                int x_goto = current.x + move[current.dir].x;
                int y_goto = current.y + move[current.dir].y;

                if ((x_goto == x_exit) && (y_goto == y_exit))
                {
                    cout << count << ":" << x_goto << "," << y_goto << endl;
                    cout << "successfully escaped!!" << endl;
                    goto endProblem;
                }

                if ((!maze[x_goto][y_goto]) && (!visited[x_goto][y_goto]))
                {
                    current.dir += 1;
                    path.push(current);
                    current.x = x_goto;
                    current.y = y_goto;
                    current.dir = E;
                    visited[x_goto][y_goto] = true;
                    cout << count++ << ":" << current.x << "," << current.y << endl;
                }
                else current.dir++;
            }
        }
        cout << "Failed to escape." << endl;

        endProblem: ;
    }
    cout << "end the code.";

    return 0;
}

vector<vector<bool> > create_maze(string filename)
{
    vector<vector<bool> > maze(SIZE);
    string line;
    int row = 0;

    ifstream inFile(filename, ios::in);
    if (!inFile)
    {
        cerr << "Failed to open " << filename << endl;
        exit(1);
    }
    while (getline(inFile, line))
    {
        for (int i = 0; i < SIZE; ++i)
        {
            maze.at(row).push_back(line.at(i) - '0');  // convert char to int
        }
        row++;
    }

    return maze;
}

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
