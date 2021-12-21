#include "Utilities.cpp"
#include <array>
#include <iostream>
#include <numeric>
#include <vector>

class Puzzle06
{

  public:
    Puzzle06();
    void SolvePartA();
    void SolvePartB();

  private:
    std::vector<int> Input;
    unsigned long long GetFishCountAfterDays(int TotalDays);
};

Puzzle06::Puzzle06()
{
    Input = Utilities::ConvertToInt(Utilities::Split(Utilities::ReadAllLinesInFile("Puzzle06.txt")[0], ","));
}

void Puzzle06::SolvePartA()
{
    std::cout << "Part A Solution: " << GetFishCountAfterDays(80) << std::endl;
}

void Puzzle06::SolvePartB()
{
    std::cout << "Part B Solution: " << GetFishCountAfterDays(256) << std::endl;
}

unsigned long long Puzzle06::GetFishCountAfterDays(int TotalDays)
{
    constexpr int LifeTime = 9;
    std::array<unsigned long long, LifeTime> CurrentFish{};

    // Initialize current fish
    for (int CurrFish : Input)
        CurrentFish[CurrFish]++;

    // Every day count down
    for (int i = 0; i < TotalDays; i++)
    {
        std::array<unsigned long long, LifeTime> NextFish{};
        NextFish[6] += CurrentFish[0]; // Fish currently timed 0 will be 6 next
        NextFish[8] += CurrentFish[0]; // Fish currently timed 0 will spawn a new fish at timed 8

        // Move fish up, next fish would be -1
        for (int j = 0; j < CurrentFish.size(); j++)
            NextFish[j - 1] += CurrentFish[j];

        CurrentFish = NextFish;
    }

    return std::accumulate(CurrentFish.begin(), CurrentFish.end(), (unsigned long long)0);
}
