#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include <numeric>

using std::array;
using std::cout;
using std::string;
using std::vector;

#define rowLength 3
#define gridSize 9

#define vt vector
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

array<int, gridSize> startGrid = {0, 1, 2, 3, 4, 5, 6, 7, 8};
array<int, gridSize> endGrid = {1, 2, 3, 4, 5, 6, 7, 8, 0};
vt<array<int, gridSize>> visitedStates{};

int move(const string &direction, const int &index);
array<int, gridSize> swap(const array<int, gridSize> &grid, const string &direction);

int main()
{
    array<int, gridSize> tempGrid{startGrid};

    visitedStates.pb(startGrid);

    while (tempGrid != endGrid)
    {
        int fValue = 0; // Need to get a new node with less fValue
        int gValue = 0; // Need to keep track of gValue

        vt<string> directions = {"up", "down", "right", "left"};

        for (const string &direction : directions)
        {
            int fValueTemp;
            int gValueTemp = gValue;
            int hValueTemp = 0; // h value is independent of current node

            array<int, gridSize> swappedGrid = swap(tempGrid, direction);

            if (std::accumulate(all(swappedGrid), 0) == 0)
            {
                continue;
            }

            gValueTemp++;

            for (int i = 0; i < gridSize; i++)
            {
                if (swappedGrid[i] != endGrid[i])
                {
                    hValueTemp++;
                }
            }

            fValueTemp = ++gValueTemp + hValueTemp;

            if (!fValue)
            {
                fValue = fValueTemp;
                gValue = gValueTemp;
            }

            if (fValueTemp < fValue)
            {
                tempGrid.swap(swappedGrid);
            }
        }

        ++gValue;
    }

    visitedStates.clear();

    return 0;
}

array<int, gridSize> swap(const array<int, gridSize> &grid, const string &direction)
{
    array<int, gridSize> returnGrid{grid};
    int zeroIndex = static_cast<int>(std::distance(grid.begin(), std::find(all(grid), 0)));

    returnGrid[zeroIndex] = returnGrid[move(direction, zeroIndex)];
    returnGrid[move(direction, zeroIndex)] = 0;

    if (std::find(all(visitedStates), returnGrid) != visitedStates.end())
    {
        std::fill(all(returnGrid), 0);
    }

    visitedStates.pb(returnGrid);

    return returnGrid;
}

int move(const string &direction, const int &index)
{
    if (direction == "up")
        return index != -1 && index - rowLength >= 0 ? index - rowLength : -1;
    if (direction == "down")
        return index != -1 && index + rowLength < gridSize ? index + rowLength : -1;
    if (direction == "right")
        return index != -1 && index % rowLength < rowLength - 1 ? index + 1 : -1;
    if (direction == "left")
        return index != -1 && index % rowLength >= 1 ? index - 1 : -1;

    return -1;
}
