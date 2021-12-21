#include "Utilities.cpp"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution
{
  private:
    static std::vector<std::string> input;
    static std::unordered_map<std::string, std::unordered_set<std::string>> graph;
    static std::vector<std::vector<std::string>> finalPaths;

  public:
    Solution();
    void SolvePartA();
    void SolvePartB();
};

std::vector<std::string> Solution::input;
std::unordered_map<std::string, std::unordered_set<std::string>> Solution::graph;
std::vector<std::vector<std::string>> Solution::finalPaths;

Solution::Solution()
{
    input = Utilities::ReadLines("AdventOfCode2021/Day12.txt");

    for (const auto &line : input)
    {
        std::vector<std::string> path = Utilities::Split(line, "-");

        // Add the bidirectional graph to the unordered set
        graph.insert(std::make_pair(path[0], std::unordered_set<std::string>()));
        graph.insert(std::make_pair(path[1], std::unordered_set<std::string>()));
        graph[path[0]].insert(path[1]);
        graph[path[1]].insert(path[0]);
    }

    // Initialize the previous paths
    std::vector<std::vector<std::string>> previousPaths({{"start"}});

    bool searchComplete = false;
    while (!searchComplete)
    {
        searchComplete = true;
        std::vector<std::vector<std::string>> currentPaths;

        for (const std::vector<std::string> &previousPath : previousPaths)
        {
            std::string currentLocation = previousPath[previousPath.size() - 1];
            std::unordered_set<std::string> caves = graph.at(currentLocation);

            for (const std::string &cave : caves)
            {
                if (cave == "start")
                {
                    continue;
                }

                if (cave == "end")
                {
                    std::vector<std::string> finalPath = previousPath;
                    finalPath.push_back(cave);
                    finalPaths.push_back(finalPath);
                    continue;
                }

                // If small cave

                std::vector<std::string> currentPath = previousPath;
                currentPath.push_back(cave);
                currentPaths.push_back(currentPath);
                searchComplete = false;
            }
        }

        previousPaths.swap(currentPaths);
    }
}

void Solution::SolvePartA()
{
    std::cout << "Part A Solution: " << finalPaths.size() << '\n';
}

void Solution::SolvePartB()
{
    std::cout << "Part B Solution: " << '\n';
}

int main()
{
    Solution solution;
    solution.SolvePartA();
    solution.SolvePartB();

    return 0;
}