#include "Utilities.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Puzzle02
{
  public:
    Puzzle02();
    void PrintSolutionA();
    void PrintSolutionB();

  private:
    std::vector<std::string> Input;
    int CalculateFinalPosition(bool bUseAim);
};
Puzzle02::Puzzle02()
{
    Input = Utilities::ReadAllLinesInFile("/Users/ajjunaidi/CLionProjects/AdventOfCode/Puzzle02.txt");
}

void Puzzle02::PrintSolutionA()
{
    std::cout << CalculateFinalPosition(false) << '\n';
}

void Puzzle02::PrintSolutionB()
{
    std::cout << CalculateFinalPosition(true) << '\n';
}

int Puzzle02::CalculateFinalPosition(bool bUseAim)
{
    int HorizontalPosition = 0;
    int Depth = 0;
    int Aim = 0;

    for (const std::string &CurrentLine : Input)
    {
        std::stringstream CurrentLineStream(CurrentLine);

        std::string Direction;
        CurrentLineStream >> Direction;

        int Magnitude = 0;
        CurrentLineStream >> Magnitude;

        if (Direction == "forward")
        {
            HorizontalPosition += Magnitude;
            if (bUseAim)
            {
                Depth += Aim * Magnitude;
            }
        }
        else if (Direction == "up")
        {
            if (bUseAim)
            {
                Aim -= Magnitude;
            }
            else
            {
                Depth -= Magnitude;
            }
        }
        else if (Direction == "down")
        {
            if (bUseAim)
            {
                Aim += Magnitude;
            }
            else
            {
                Depth += Magnitude;
            }
        }
        else
        {
            Utilities::VerifyNotReached();
        }
    }

    return HorizontalPosition * Depth;
}
