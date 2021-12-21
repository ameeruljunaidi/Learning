#include "Utilities.cpp"
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Solution
{
  private:
    static std::set<std::pair<int, int>> manual;
    static std::vector<std::pair<char, int>> instructions;
    static int foldManual(int foldCount);
    static void printManual();

  public:
    Solution();
    static void SolvePartA();
    static void SolvePartB();
};

std::set<std::pair<int, int>> Solution::manual;
std::vector<std::pair<char, int>> Solution::instructions;

Solution::Solution()
{
    std::vector<std::string> input = Utilities::ReadLines("AdventOfCode2021/Day13.txt");

    for (const std::string &line : input)
    {
        // manual is formatted as a set which each element of type pair
        // First element is the column and second element is the row
        // Need to go through every line in the input
        // If it can be split by a comma, then it is a dot coordinate
        // Clear lineSplit before checking if instruction

        std::vector<std::string> lineSplit = Utilities::Split(line, ",");
        if (lineSplit.size() == 2)
        {
            int column = std::stoi(lineSplit[0]);
            int row = std::stoi(lineSplit[1]);
            std::pair<int, int> dotCoordinate = {column, row};
            manual.insert(dotCoordinate);
        }
        lineSplit.clear();

        // Format is "fold along y=7"
        // If we can be split by the = delimiter, then it is an instruction
        // The instructions variable is a vector with pair as elements
        // Need to take the last element of the first element of the split for the fold type (x or y)
        // Need to convert the second element to int and adding pushing it to the back of the vector

        lineSplit = Utilities::Split(line, "=");
        if (lineSplit.size() == 2)
        {
            char foldType = lineSplit[0][lineSplit[0].size() - 1];
            int foldAt = std::stoi(lineSplit[1]);
            std::pair<char, int> instruction = {foldType, foldAt};
            instructions.push_back(instruction);
        }
    }
}

int Solution::foldManual(int foldCount)
{
    int counter = 0;
    for (const std::pair<char, int> instruction : instructions)
    {
        // There two ways that it can be folded, each required to be treated differently
        // Regardless of folding type, the general idea is the same
        // Only consider the bottom half if fold at y and only consider the right half if fold at x
        // Need to first get the coordinate of the folded dot
        // Remove the old pair (dot) in the set and add the new dot
        // If there is already a dot there, shouldn't be a problem since is a set

        if (instruction.first == 'x')
        {
            int foldAt = instruction.second;
            for (std::pair<int, int> dot : manual)
            {
                int column = dot.first;
                int row = dot.second;

                if (column < foldAt)
                {
                    continue;
                }

                int distance = column - foldAt;
                int newColumn = foldAt - distance;
                std::pair<int, int> newDot = {newColumn, row};
                manual.insert(newDot);
            }

            for (auto it = manual.begin(); it != manual.end();)
            {
                int column = it->first;

                if (column > foldAt)
                {
                    it = manual.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        if (instruction.first == 'y')
        {
            int foldAt = instruction.second;
            for (std::pair<int, int> dot : manual)
            {
                int column = dot.first;
                int row = dot.second;

                if (row < foldAt)
                {
                    continue;
                }

                int distance = row - foldAt;
                int newRow = foldAt - distance;
                std::pair<int, int> newDot =  {column, newRow};
                manual.insert(newDot);
            }

            for (auto it = manual.begin(); it != manual.end();)
            {
                int row = it->second;

                if (row > foldAt)
                {
                    it = manual.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        counter++;
        if (counter == foldCount)
        {
            break;
        }
    }
    return static_cast<int>(manual.size());
}

void Solution::printManual()
{
    int maxColumn = 0;
    int maxRow = 0;

    for (std::pair<int, int> dot : manual)
    {
        int column = dot.first;
        int row = dot.second;

        if (column > maxColumn)
        {
            maxColumn = column;
        }

        if (row > maxRow)
        {
            maxRow = row;
        }
    }

    std::vector<std::vector<char>> grid(maxRow + 1, std::vector<char>(maxColumn + 1, '.'));

    for (std::pair<int, int> dot : manual)
    {
        int column = dot.first;
        int row = dot.second;

        grid[row][column] = '#';
    }

    std::cout << '\n';
    for (const std::vector<char> &line : grid)
    {
        for (const char &dot : line)
        {
            std::cout << dot << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Solution::SolvePartA()
{
    std::cout << "Part A Solution: " << foldManual(1) << '\n';
    printManual();
}

void Solution::SolvePartB()
{
    std::cout << "Part B Solution: " << foldManual((int)instructions.size()) << '\n';
    printManual();
}

int main()
{
    Solution solution;
//     solution.SolvePartA();
     solution.SolvePartB();

    return 0;
}