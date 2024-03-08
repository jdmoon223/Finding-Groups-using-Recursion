/*
 * Name: Jeffrey Moon
 * Date Submitted: 02/12/2024
 * Lab Section: 001
 * Assignment Name: Finding Groups using Recursion
 */

#include "Grouping.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below
Grouping::Grouping(string fileName){
    ifstream infile(fileName);  // Open the file specified by fileName for reading
    char character;  // Declare a variable to store characters read from the file

    // Check if the file opened correctly
    if (!infile.is_open()){
        cout << "Error: file did not open successfully";
    }

    // Loop through the grid (assuming it's a 10x10 grid)
    for(int i = 0; i < 10; i++){ // loop through the colulums
        for (int j = 0; j < 10; j++ ){ //loop through the rows
            infile >> character;  // Read a character from the file
            if (character == '.'){
                grid[i][j] = 0;  // If the character is '.', set grid[i][j] to 0
            }
            else{
                grid[i][j] = 1;  // Otherwise, set grid[i][j] to 1
            }
        }
    }

    // Loop through the grid to find groups of connected squares
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (grid[i][j] == 1){  // If the current square is part of a group
                groups.push_back(vector<GridSquare>());  // Create a new group
                findGroup(i, j);  // Call findGroup function to find all squares in the group
            }
        }
    }
}

void Grouping::findGroup(int r, int c) {
    grid[r][c] = 0;  // Mark the current square as visited
    groups.back().push_back(GridSquare(r, c));  // Add the current square to the current group

    // Check adjacent squares and recursively call findGroup if they are part of the group
    if (r + 1 < 10){
        if (grid[r + 1][c] == 1){
            findGroup(r + 1, c);
        }
    }
    if (r - 1 >= 0){
        if (grid[r - 1][c] == 1){
            findGroup(r - 1, c);
        }
    }
    if (c + 1 < 10){
        if (grid[r][c + 1] == 1){
            findGroup(r, c + 1);
        }
    }
    if (c - 1 >= 0){
        if (grid[r][c - 1] == 1){
            findGroup(r, c - 1);
        }
    }
}

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}