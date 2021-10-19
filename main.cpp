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

#define SIZE 17
vector<vector<int> > create_maze(string filename);
void print(vector<vector<int> > array);

struct position
{
    int x, y, dir;
};

struct offsets
{
    int x, y;
};

int main()
{
    string filename;
    vector<vector<int> > maze;
    vector<vector<int> > visited;
    const vector<offsets> move;
    enum directions {E, S, N, W};
    stack<position> path;

    cout << "enter filename : ";
    cin >> filename;
    maze = create_maze(filename);
    print(maze);

    int x_start, y_start, x_end, y_end;
    while (true)
    {
        cout << "enter start position : ";
        cin >> x_start >> y_start;
        if ((x_start == -1) && (y_start == -1)) { break; }
        cout << "enter exit position : ";
        cin >> x_end >> y_end;
        if ((x_end == -1) && (y_end == -1)) { break; }
    }

    return 0;
}

vector<vector<int> > create_maze(string filename)
{
    vector<vector<int> > maze(SIZE);
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

void print(vector<vector<int> > array)
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            cout << array[i][j];
        }
        cout << endl;
    }
}
