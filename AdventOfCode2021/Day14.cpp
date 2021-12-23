#include "Utilities.cpp"
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
  private:
    static std::vector<std::string> input;
    static std::string polymer;
    static std::unordered_map<std::string, std::string> pairs;
    static std::unordered_map<char, int> charCount;
    static int MostLeastElementDifference();

  public:
    Solution();
    static void Solve();
};

std::vector<std::string> Solution::input;
std::string Solution::polymer;
std::unordered_map<std::string, std::string> Solution::pairs;
std::unordered_map<char, int> Solution::charCount;

Solution::Solution()
{
    input = Utilities::ReadLines("AdventOfCode2021/Day14.txt");

    int lineCounter = 0;
    for (const std::string &line : input)
    {
        if (lineCounter == 0)
        {
            polymer = line;
            lineCounter++;
            continue;
        }

        std::vector<std::string> splitLine = Utilities::Split(line, " -> ");
        pairs[splitLine[0]] = splitLine[1];
    }
}

int Solution::MostLeastElementDifference()
{
    // Function returns the count of the majority element and the minority element
    // Go through the string n number of times
    // Create a copy of the polymer first
    // Need to access the index of the string and loop through
    // Find if the combination of letters exists in the pairs
    // Insert into the current position

    int steps = 40;
    for (int x = 0; x < steps; x++)
    {
        std::string copyPolymer(polymer);

        int insertIndex = 0; //  Keeps track of the index to insert the character
        for (int i = 1; i < polymer.size(); i++)
        {
            std::string substring = polymer.substr(i - 1, 2);
            copyPolymer.insert(i + insertIndex, pairs[substring]);
            insertIndex++;
        }

        polymer.swap(copyPolymer);
    }

    // Initialize the count map
    for (char i = 'A'; i <= 'Z'; i++)
    {
        charCount[i] = 0;
    }

    for (const char &character : polymer)
    {
        charCount[character]++;
    }

    int minValue = static_cast<int>(polymer.size());
    int maxValue = 0;
    for (const auto &[key, value] : charCount)
    {
        if (value == 0)
        {
            continue;
        }
        if (value < minValue)
        {
            minValue = value;
        }
        if (value > maxValue)
        {
            maxValue = value;
        }
    }

    return maxValue - minValue;
}

void Solution::Solve()
{
    std::cout << "Solution: " << MostLeastElementDifference() << '\n';
}

int main()
{
    Solution solution;
    solution.Solve();

    return 0;
}
