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
    static int countPaths(bool smallCaveOnce);

  public:
    Solution();
    void SolvePartA();
    void SolvePartB();
};

std::vector<std::string> Solution::input;
std::unordered_map<std::string, std::unordered_set<std::string>> Solution::graph;

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
}

int Solution::countPaths(bool smallCaveOnce)
{
    // Initialize the previous paths
    std::vector<std::vector<std::string>> finalPaths;
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

                if (cave[0] >= 'a' && cave[0] <= 'z')
                {
                    bool visited = std::find(previousPath.begin(), previousPath.end(), cave) != previousPath.end();
                    if (visited)
                    {
                        if (smallCaveOnce)
                        {
                            continue;
                        }

                        // If it is already visited, and vising a small cave twice is allowed
                        // Need to check first if there is already a duplicate small cave in previous path
                        // If there is already a duplicated small cave in previous path
                        // Then need to break out of the loop
                        // To find if there is already a duplicate, sort the vector first
                        // Then find the duplicate

                        bool duplicatedSmallCaveExist = false;
                        for (int i = 1; i < previousPath.size(); i++)
                        {
                            std::string previousCave = previousPath[i];

                            if (previousCave[0] >= 'a' && previousCave[0] <= 'z')
                            {
                                duplicatedSmallCaveExist = std::find(previousPath.begin() + i + 1, previousPath.end(), previousCave) != previousPath.end();
                                if (duplicatedSmallCaveExist)
                                {
                                    break;
                                }
                            }
                        }

                        if (duplicatedSmallCaveExist)
                        {
                            continue;
                        }
                    }
                }

                std::vector<std::string> currentPath = previousPath;
                currentPath.push_back(cave);
                currentPaths.push_back(currentPath);
                searchComplete = false;
            }
        }

        previousPaths.swap(currentPaths);
    }

    return static_cast<int>(finalPaths.size());
}

void Solution::SolvePartA()
{
    std::cout << "Part A Solution: " << countPaths(true) << '\n';
}

void Solution::SolvePartB()
{
    std::cout << "Part B Solution: " << countPaths(false) << '\n';
}

int main()
{
    Solution solution;
    solution.SolvePartA();
    solution.SolvePartB();

    return 0;
}