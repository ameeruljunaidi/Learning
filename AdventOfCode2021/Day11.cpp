#include "Utilities.cpp"
#include <array>
#include <iostream>
#include <unordered_set>
#include <vector>

class Puzzle11
{
  private:
    static std::vector<std::string> Input;
    static std::vector<int> OctopusMap;
    static int RowLength;
    static void PrintMap();
    static int GoUp(int i);
    static int GoDown(int i);
    static int GoRight(int i);
    static int GoLeft(int i);
    static int CountTotalFlashes(int DayCount);
    static int CheckFlash();
    static void FlashOctopus(int Index, std::unordered_set<int> &FlashedIndices);
    static int FindSimultaneousFlash();

  public:
    explicit Puzzle11(const std::string &FileName);
    void SolvePartA();
    void SolvePartB();
};

std::vector<std::string> Puzzle11::Input;
std::vector<int> Puzzle11::OctopusMap;
int Puzzle11::RowLength = 0;

Puzzle11::Puzzle11(const std::string &FileName)
{
    Input = Utilities::ReadAllLinesInFile(FileName);
    for (const std::string &CurrentLine : Input)
    {
        for (const char &CurrentChar : CurrentLine)
        {
            OctopusMap.push_back(CurrentChar - '0');
        }

        if (RowLength == 0)
        {
            RowLength = static_cast<int>(CurrentLine.size());
        }
    }
}

void Puzzle11::SolvePartA()
{
    int DayCount = 100;
    std::cout << "Solution A: " << CountTotalFlashes(DayCount) << " flashes in " << DayCount << " days " << '\n';
}

void Puzzle11::SolvePartB()
{
    std::cout << "Solution B: " << FindSimultaneousFlash() << '\n';
}

int Puzzle11::CountTotalFlashes(int DayCount)
{
    int CountTotalFlashes = 0;

    // go through every day and flash the octopus map
    for (int i = 0; i < DayCount; i++)
    {
        for (int j = 0; j < OctopusMap.size(); j++)
        {
            OctopusMap[j]++;
        }

        CountTotalFlashes += CheckFlash();
    }

    return CountTotalFlashes;
}

int Puzzle11::CheckFlash()
{
    std::unordered_set<int> FlashedIndices;

    for (int i = 0; i < OctopusMap.size(); i++)
    {
        if (OctopusMap[i] > 9)
        {
            FlashOctopus(i, FlashedIndices);
        }
    }

    return static_cast<int>(FlashedIndices.size());
}

void Puzzle11::FlashOctopus(int Index, std::unordered_set<int> &FlashedIndices)
{
    if (Index == -1 || FlashedIndices.find(Index) != FlashedIndices.end())
    {
        return;
    }

    if (OctopusMap[Index] < 9)
    {
        OctopusMap[Index]++;
        return;
    }

    FlashedIndices.insert(Index);
    OctopusMap[Index] = 0;

    FlashOctopus(GoUp(Index), FlashedIndices);
    FlashOctopus(GoDown(Index), FlashedIndices);
    FlashOctopus(GoLeft(Index), FlashedIndices);
    FlashOctopus(GoRight(Index), FlashedIndices);
    FlashOctopus(GoUp(GoLeft(Index)), FlashedIndices);
    FlashOctopus(GoUp(GoRight(Index)), FlashedIndices);
    FlashOctopus(GoDown(GoLeft(Index)), FlashedIndices);
    FlashOctopus(GoDown(GoRight(Index)), FlashedIndices);
}

int Puzzle11::FindSimultaneousFlash()
{
    int Step = 0;
    while (true)
    {
        ++Step;
        for (int i = 0; i < OctopusMap.size(); ++i)
        {
            ++OctopusMap[i];
        }

        if (CheckFlash() == OctopusMap.size())
        {
            return Step;
        }
    }
}

int Puzzle11::GoUp(int i)
{
    return i != -1 && i - RowLength >= 0 ? i - RowLength : -1;
}

int Puzzle11::GoDown(int i)
{
    return i != -1 && i + RowLength < OctopusMap.size() ? i + RowLength : -1;
}

int Puzzle11::GoRight(int i)
{
    return i != -1 && i % RowLength < RowLength - 1 ? i + 1 : -1;
}

int Puzzle11::GoLeft(int i)
{
    return i != -1 && i % RowLength >= 1 ? i - 1 : -1;
}

void Puzzle11::PrintMap()
{
    std::cout << '\n';
    int CurrentColumn = 0;
    for (int i = 0; i < OctopusMap.size(); i++)
    {
        std::cout << OctopusMap[i];
        CurrentColumn++;

        if (CurrentColumn == RowLength)
        {
            std::cout << '\n';
            CurrentColumn = 0;
        }
    }
    std::cout << '\n';
}
