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
#include <string>

#define SIZE 17

int main()
{
    std::string filename;
    int maze[SIZE][SIZE];

    std::cout << "enter filename : ";
    std::cin >> filename;
    std::ifstream inFile(filename, std::ios::in);

    if (!inFile)
    {
        std::cerr << "Failed to open " << filename << std::endl;
        exit(1);
    }

    std::string line;
    int row = 0;
    while (getline(inFile, line))
    {
        for (int i = 0; i < SIZE - 1; ++i)
        {
            maze[row][i] = line.at(i) - '0';  // convert char to int
        }
        row++;
    }

    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
