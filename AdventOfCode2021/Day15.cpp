#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

#define vt vector
#define pb push_back

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
int move(const string &direction, int index, const int &rowLength, const int &mapSize)
{
    if (direction == "up")
        return index != -1 && index - rowLength >= 0 ? index - rowLength : -1;
    if (direction == "down")
        return index != -1 && index + rowLength < mapSize ? index + rowLength : -1;
    if (direction == "right")
        return index != -1 && index % rowLength < rowLength - 1 ? index + 1 : -1;
    if (direction == "left")
        return index != -1 && index % rowLength >= 1 ? index - 1 : -1;

    return -1;
}

/**
 * @param flatMap is the map itself
 * @param rowLength is the length of the floor
 * @return an int of the lowest total risk
 */
int lowestTotalRisk(const vt<int> &flatMap, const int &rowLength)
{

    return 0;
}

int main()
{
    vt<string> input = readLinesInFile("AdventOfCode2021/Day15.txt");
    vt<int> flatMap;
    int rowLength = 0;

    for (const string &line : input)
    {
        for (char c : line)
            flatMap.pb(c - '0');

        if (rowLength == 0)
            rowLength = static_cast<int>(line.size());
    }

    cout << "Part A Solution: " << lowestTotalRisk(flatMap, rowLength) << '\n';

    return 0;
}