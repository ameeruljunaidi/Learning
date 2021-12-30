#include <algorithm>
#include <cassert>
#include <climits>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using std::cout;
using std::string;
using std::unordered_set;
using std::vector;

#define vt vector
#define pb push_back
#define u_set unordered_set
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

static vt<string> input;
static vt<int> flatMap;
static int rowLength = 0;

vt<string> readLinesInFile(const std::filesystem::path &path);
int move(const string &direction, const int &index);
int dijkstraDistance();

int main()
{
    input = readLinesInFile("AdventOfCode2021/Day15.txt");
    int rl = sz(input[0]); // row length
    int cl = sz(input);    // column length

    // Part A
    {
        rowLength = rl;

        for (const string &line : input)
        {
            for (char c : line)
                flatMap.pb(c - '0');
        }

        cout << "Part A Solution: " << dijkstraDistance() << '\n';

        flatMap.clear();
        rowLength = 0;
    }

    // Part B
    {
        const int m = 5;       // multiplier
        rowLength = rl * m;

        int mci = 0; // index column multiplier
        for (int i = 0; i < sz(input) * m; ++i)
        {
            int mri = 0; // index row multiplier
            for (int j = 0; j < sz(input[i % cl]) * m; ++j)
            {
                int cost = (input[i % cl][j % rl] - '0') + mri + mci;
                flatMap.pb((cost < 10 ? cost : cost - 9));

                mri = j % rl == rl - 1 ? ++mri : mri;
            }
            mci = i % cl == cl - 1 ? ++mci : mci;
        }

        cout << "Part B Solution: " << dijkstraDistance() << '\n';

        flatMap.clear();
        rowLength = 0;
    }

    return 0;
}

/**
 * @param path of the file to read
 * @return a vector of all the lines in the file
 */
vt<string> readLinesInFile(const std::filesystem::path &path)
{
    assert(std::filesystem::exists(path));

    vt<string> all_lines;
    std::ifstream file_stream(path);
    string current_line;

    while (getline(file_stream, current_line))
    {
        all_lines.push_back(current_line);
    }

    return all_lines;
}

/**
 * @param direction to go: up, down, right, or left
 * @param index of the current location
 * @param rowLength of the flat map
 * @param mapSize is the total size of the flatMap vector
 * @return -1 if not a valid move, returns an index to go to if valid
 */
int move(const string &direction, const int &index)
{
    if (direction == "up")
        return index != -1 && index - rowLength >= 0 ? index - rowLength : -1;
    if (direction == "down")
        return index != -1 && index + rowLength < sz(flatMap) ? index + rowLength : -1;
    if (direction == "right")
        return index != -1 && index % rowLength < rowLength - 1 ? index + 1 : -1;
    if (direction == "left")
        return index != -1 && index % rowLength >= 1 ? index - 1 : -1;

    return -1;
}

/**
 * No parameters, work on global variable declared at top of file
 *
 * @return the most efficient path to end
 */
int dijkstraDistance()
{
    auto unvisitedIndices = u_set<int>();
    auto distance = vt<int>{};
    for (auto i = 0; i < sz(flatMap); ++i)
    {
        unvisitedIndices.insert(i);
        distance.pb(INT_MAX);
    }
    distance[0] = 0;
    auto distanceLookup = vt<const int *>{}; // Vector that holds pointers to int
    distanceLookup.pb(&distance[0]);         // Push back the memory address of the int

    // The distance vector a vector that holds the distance at each index of the map from start to that index location
    // The distance lookup vector is a vector that holds pointers to int (int values from the original distance vector)

    while (!unvisitedIndices.empty())
    {
        // Select node to process
        const int *nextEntry = distanceLookup.back(); // Get pointer to int of the latest elements pushed
        int nextNodeIndex = static_cast<int>(nextEntry - &distance[0]);

        // * This is some pointer arithmetic bullshit, need to really understand this
        // The nextEntry pointer looks to the last location pushed back to the distanceLookup
        // &distance[0] is the first location (the start location)
        // The distance between them would give the index of that location (the latest one pushed back on to
        // distanceLookup) on the original flatMap and store in nextNodeIndex

        // Visit the element
        distanceLookup.pop_back();             // Remove the latest entry pushed back (we only needed it to get the
                                               // flatMap index
        unvisitedIndices.erase(nextNodeIndex); // Remove the index that we have in the unvisitedIndicesMap

        // Update neighbors
        bool distancesUpdated = false;

        /**
         * This is where the bulk of the Dijkstra's algorithm is implemented (in the updateNeighbor) function
         * The capture [&] captures all available variables outside the scope of the function by reference
         * @param neighborIndex is the index of the surrounding location around the current location
         * @return void
         */
        auto updateNeighbor = [&](int neighborIndex) {
            // neighborIndex is a function that checks (if -1 means it is not a valid index for the map)
            // neighborIndex should also exist in the unvisitedIndices set (we are only updating unvisited neighbors)
            if (neighborIndex == -1 || unvisitedIndices.find(neighborIndex) == unvisitedIndices.end())
            {
                return;
            }

            // updatedDistance is going to be the distance from start to that particular index location
            // We get this by adding its own cost (flatMap[neighbourIndex]) to the distance[nextNodeIndex]
            // Then we check if the new updated distance is less than the current distance we have in our record
            // If it is a better distance (lower cost), then we update the distance at that particular index location
            // If that index location is updated, need to add it to the distanceLookup vector
            // But only add it to the distanceLookup vector if it does not exist in the vector
            // This is because we do not want to have visited an index location twice
            // Also need to keep track if the distances is updated because the distanceLookup table need to sorted
            // in a min PQ-like structure

            int updatedDistance = distance[nextNodeIndex] + flatMap[neighborIndex];
            if (updatedDistance < distance[neighborIndex])
            {
                distance[neighborIndex] = updatedDistance;

                if (std::find(all(distanceLookup), &distance[neighborIndex]) == distanceLookup.end())
                    distanceLookup.pb(&distance[neighborIndex]);

                distancesUpdated = true;
            }
        };

        updateNeighbor(move("up", nextNodeIndex));
        updateNeighbor(move("down", nextNodeIndex));
        updateNeighbor(move("left", nextNodeIndex));
        updateNeighbor(move("right", nextNodeIndex));

        // Sort the distanceLookup table, the order need to be like a min PQ structure
        // However, since the distanceLookup table holds pointers rather than values, need to use a lambda
        // int *&left and int *&right looks weird, but it's basically a parameter that is referencing a pointer to int
        // return *left > *right is de-referencing the pointer because we want to compare the value itself not the
        // memory location of the location index

        if (distancesUpdated)
        {
            std::sort(all(distanceLookup), [](const int *&left, const int *&right) { return *left > *right; });
        }
    }

    return distance[sz(flatMap) - 1];
}