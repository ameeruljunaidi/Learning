#include <fstream>
#include <iostream>
#include <vector>

class Puzzle01
{
  public:
    Puzzle01()
    {
        std::ifstream fin("AdventOfCode2021/Inputs/Day01.txt");
        std::string input;

        while (true)
        {
            getline(fin, input);
            if (input.empty())
                break;
            int currentInput = stoi(input);
            depths.push_back(currentInput);
        }
    }

    static void PrintSolutionA();
    static void PrintSolutionB();

  private:
    std::vector<int> depths;
    static int CountIncreasingDepthMeasurements(const Puzzle01 &puzzle);
    static int CountIncreasingDepthWindows(const Puzzle01 &puzzle);
};

void Puzzle01::PrintSolutionA()
{
    Puzzle01 puzzle01;
    int answer = CountIncreasingDepthMeasurements(puzzle01);
    std::cout << answer << "\n";
}

void Puzzle01::PrintSolutionB()
{
    Puzzle01 puzzle01;
    int answer = CountIncreasingDepthWindows(puzzle01);
    std::cout << answer << "\n";
}

int Puzzle01::CountIncreasingDepthMeasurements(const Puzzle01 &puzzle)
{
    int increasingDepthMeasurement = 0;
    for (int i = 1; i < puzzle.depths.size(); i++)
    {
        int previousMeasurement = puzzle.depths[i - 1];
        int currentMeasurement = puzzle.depths[i];
        if (currentMeasurement > previousMeasurement)
        {
            increasingDepthMeasurement++;
        }
    }
    return increasingDepthMeasurement;
}

int Puzzle01::CountIncreasingDepthWindows(const Puzzle01 &puzzle)
{
    int increasingDepthMeasurement = 0;
    for (int i = 3; i < puzzle.depths.size(); i++)
    {
        int previousWindow = puzzle.depths[i - 1] + puzzle.depths[i - 2] + puzzle.depths[i - 3];
        int currentWindow = puzzle.depths[i] + puzzle.depths[i - 1] + puzzle.depths[i - 2];
        if (currentWindow > previousWindow)
        {
            increasingDepthMeasurement++;
        }
    }
    return increasingDepthMeasurement;
}
