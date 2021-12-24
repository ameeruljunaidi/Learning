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
    static std::unordered_map<std::string, unsigned long long> pairCount;
    static int PartASolver();
    static unsigned long long PartBSolver();
    static void PrintPolymer();

  public:
    Solution();
    static void SolvePartA();
    static void SolvePartB();
};

std::vector<std::string> Solution::input;
std::string Solution::polymer;
std::unordered_map<std::string, std::string> Solution::pairs;
std::unordered_map<char, int> Solution::charCount;
std::unordered_map<std::string, unsigned long long> Solution::pairCount;

Solution::Solution()
{
    input = Utilities::ReadLines("Day14.txt");

    int lineCounter = 0;
    for (const std::string &line : input)
    {
        if (lineCounter == 0)
        {
            polymer = line;
            lineCounter++;
            continue;
        }

        if (lineCounter == 1)
        {
            lineCounter++;
            continue;
        }

        std::vector<std::string> splitLine = Utilities::Split(line, " -> ");
        pairs[splitLine[0]] = splitLine[1];
    }

    // Initialize the pairCount map
    for (auto [key, value] : pairs)
    {
        pairCount[key] = 0;
    }

    for (size_t i = 1; i < polymer.size(); i++)
    {
        pairCount[polymer.substr(i - 1, 2)]++;
    }
}

int Solution::PartASolver()
{
    // Function returns the count of the majority element and the minority element
    // Go through the string n number of times
    // Create a copy of the polymer first
    // Need to access the index of the string and loop through
    // Find if the combination of letters exists in the pairs
    // Insert into the current position

    int steps = 10;
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

        polymer = std::move(copyPolymer);
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
    for (auto [key, value] : charCount)
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

unsigned long long Solution::PartBSolver()
{
    // Create a static variable map with pair and count called pairCount
    // Initialize them all to zero
    // Work only from this map
    // Loop through the map n (steps) number of times
    // If a pair is found in the pairs map, then that pair will become 0
    // Then add 1 to substring 0,1 + additional char & same with substring 1,1

    size_t totalIterations = 40;
    for (size_t i = 0; i < totalIterations; i++)
    {
        auto nextPairCount = std::unordered_map<std::string, unsigned long long>{};

        for (const auto &pair : pairCount)
        {
            const auto &currentPair = pair.first;
            const auto &currentCount = pair.second;
            const auto &substitution = pairs.at(currentPair);

            auto firstPair = std::string{currentPair[0], substitution[0]};
            nextPairCount.try_emplace(firstPair, 0);
            nextPairCount[firstPair] += currentCount;

            auto secondPair = std::string{substitution[0], currentPair[1]};
            nextPairCount.try_emplace(secondPair, 0);
            nextPairCount[secondPair] += currentCount;
        }

        pairCount = std::move(nextPairCount);
    }

    std::unordered_map<char, unsigned long long> elementCount;
    elementCount[polymer[0]] = 1;
    for (const auto &pair : pairCount)
    {
        const auto &currentPair = pair.first;
        const auto &currentCount = pair.second;
        elementCount.try_emplace(currentPair[1], 0);
        elementCount[currentPair[1]] += currentCount;
    }

    auto compare = [](const auto &left, const auto &right) { return left.second < right.second; };
    const auto &minOccurences = std::min_element(elementCount.begin(), elementCount.end(), compare);
    const auto &maxOccurences = std::max_element(elementCount.begin(), elementCount.end(), compare);

    return maxOccurences->second - minOccurences->second;
}

void Solution::PrintPolymer()
{
    std::cout << '\n';
    for (auto [key, value] : pairCount)
    {
        if (value > 0)
        {
            std::cout << key << " ";
        }
    }
    std::cout << '\n';
    for (auto [key, value] : pairCount)
    {
        if (value > 0)
        {
            std::cout << value << "  ";
        }
    }
    std::cout << '\n';
}

void Solution::SolvePartA()
{
    std::cout << "Part A Solution: " << PartASolver() << '\n';
}

void Solution::SolvePartB()
{
    std::cout << "Part B Solution: " << PartBSolver() << '\n';
}

int main()
{
    Solution solution;
    // solution.SolvePartA();
    solution.SolvePartB();

    return 0;
}
