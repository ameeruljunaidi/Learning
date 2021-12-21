#include "Utilities.cpp"
#include <iostream>
#include <string>
#include <vector>

struct Coordinates
{
    int x1;
    int x2;
    int y1;
    int y2;
};

class Puzzle05
{
  public:
    std::vector<std::vector<int>> Grid;
    Puzzle05();
    void SolvePartA();
    void SolvePartB();
    void PrintGrid();
    void MarkVerticalHorizontal();
    void MarkDiagonal();
    int GetOverlapCount(std::string Part);

  private:
    std::vector<std::string> Input;
    std::vector<Coordinates> Lines;
    int GridSize;
};

Puzzle05::Puzzle05()
{
    Input = Utilities::ReadAllLinesInFile("Puzzle05.txt");

    std::vector<std::string> XInputs, YInputs;
    // Split line by arrow
    for (const std::string &Line : Input)
    {
        std::vector<std::string> LineSplit = Utilities::Split(Line, " -> ");
        XInputs.push_back(LineSplit[0]);
        YInputs.push_back(LineSplit[1]);
    }

    Utilities::VerifyElseCrash(XInputs.size() == YInputs.size());

    // Split by comma
    std::vector<int> SplitLeftInputs, SplitRightInputs;
    for (int i = 0; i < XInputs.size(); i++)
    {
        SplitLeftInputs = Utilities::ConvertToInt(Utilities::Split(XInputs[i], ","));
        SplitRightInputs = Utilities::ConvertToInt(Utilities::Split(YInputs[i], ","));

        Coordinates NewLine{};
        NewLine.x1 = SplitLeftInputs[0];
        NewLine.y1 = SplitLeftInputs[1];
        NewLine.x2 = SplitRightInputs[0];
        NewLine.y2 = SplitRightInputs[1];
        Lines.push_back(NewLine);
        SplitLeftInputs.clear();
        SplitRightInputs.clear();
    }

    // Get grid size
    int MaxGridSize = 0;
    for (Coordinates Coordinate : Lines)
    {
        if (Coordinate.x1 > MaxGridSize)
            MaxGridSize = Coordinate.x1;
        if (Coordinate.x2 > MaxGridSize)
            MaxGridSize = Coordinate.x2;
        if (Coordinate.y1 > MaxGridSize)
            MaxGridSize = Coordinate.y1;
        if (Coordinate.y2 > MaxGridSize)
            MaxGridSize = Coordinate.y2;
    }
    // +1 because inclusive 0
    GridSize = MaxGridSize + 1;

    // Initialize grid
    std::vector<int> GridRow;
    for (int i = 0; i < GridSize; i++)
    {
        GridRow.reserve(GridSize);
        for (int j = 0; j < GridSize; j++)
            GridRow.push_back(0);
        Grid.push_back(GridRow);
        GridRow.clear();
    }
}

void Puzzle05::SolvePartA()
{
    std::cout << "Solve Part A: " << GetOverlapCount("A") << std::endl;
}

void Puzzle05::SolvePartB()
{
    std::cout << "Solve Part B: " << GetOverlapCount("B") << std::endl;
}

void Puzzle05::PrintGrid()
{
    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (Grid[i][j] == 0)
                std::cout << "."
                          << " ";
            else
                std::cout << Grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Puzzle05::MarkVerticalHorizontal()
{
    for (Coordinates Coordinate : Lines)
    {
        int x1 = std::min(Coordinate.x1, Coordinate.x2);
        int x2 = std::max(Coordinate.x1, Coordinate.x2);
        int y1 = std::min(Coordinate.y1, Coordinate.y2);
        int y2 = std::max(Coordinate.y1, Coordinate.y2);

        if (x1 == x2 || y1 == y2)
        {
            for (int i = x1; i <= x2; i++)
            {

                for (int j = y1; j <= y2; j++)
                {
                    Grid[j][i]++;
                }
            }
        }
    }
}

void Puzzle05::MarkDiagonal()
{
    for (Coordinates Coordinate : Lines)
    {
        int x1 = Coordinate.x1;
        int x2 = Coordinate.x2;
        int y1 = Coordinate.y1;
        int y2 = Coordinate.y2;
        // need to check for 45 degree
        // example 9, 7 -> 7, 9 which covers 9,7 , 8,8 , and 7,9
        if (std::abs(x2 - x1) == std::abs(y2 - y1))
        {
            // two ways diagonally
            // if x1 > x2
            if (x1 > x2 && y1 > y2)
            {
                for (int i = 0; i <= std::abs(x2 - x1); i++)
                    Grid[y1 - i][x1 - i]++;
            }
            else if (x1 < x2 && y1 > y2)
            {
                for (int i = 0; i <= std::abs(x2 - x1); i++)
                    Grid[y1 - i][x1 + i]++;
            }
            else if (x1 < x2 && y1 < y2)
            {
                for (int i = 0; i <= std::abs(x2 - x1); i++)
                    Grid[y1 + i][x1 + i]++;
            }
            else if (x1 > x2 && y1 < y2)
            {
                for (int i = 0; i <= std::abs(x2 - x1); i++)
                    Grid[y1 + i][x1 - i]++;
            }
        }
    }
}

int Puzzle05::GetOverlapCount(std::string Part)
{
    if (Part == "A")
        MarkVerticalHorizontal();
    else if (Part == "B")
        MarkDiagonal();
    int Count = 0;
    for (int i = 0; i < GridSize; i++)
        for (int j = 0; j < GridSize; j++)
            if (Grid[i][j] >= 2)
                Count++;
    ;
    return Count;
}
