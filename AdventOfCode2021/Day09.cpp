#include "Utilities.cpp"
#include <algorithm>
#include <iostream>
#include <vector>

class Puzzle09
{
  private:
    std::vector<std::vector<int>> HeightMap;
    std::vector<std::vector<bool>> HeightMapChecker;

  public:
    Puzzle09();
    void ResetChecker();
    void SolvePartA();
    void SolvePartB();
    bool ValidPosition(int i, int j, int m, int n);
    bool IsBasin(int i, int j);
    int LowPointsRiskLevel();
    int GetBasinSize(int i, int j);
    int ThreeLargestBasin();
};

Puzzle09::Puzzle09()
{
    std::vector<std::string> Input = Utilities::ReadAllLinesInFile("Puzzle09.txt");
    for (const auto &LineInput : Input)
    {
        std::vector<int> VectorConvert;
        for (const auto &Number : LineInput)
        {
            int NumberConvert = Number - '0';
            VectorConvert.push_back(NumberConvert);
        }

        HeightMap.push_back(VectorConvert);
        VectorConvert.clear();
    }

    for (auto &i : HeightMap)
    {
        std::vector<bool> TempVector;
        TempVector.reserve(i.size());
        for (int j = 0; j < i.size(); j++)
            TempVector.push_back(false);
        HeightMapChecker.push_back(TempVector);
        TempVector.clear();
    }
}

void Puzzle09::ResetChecker()
{
    for (int i = 0; i < HeightMap.size(); i++)
    {
        for (int j = 0; j < HeightMap[i].size(); j++)
            HeightMapChecker[i][j] = false;
    }
}

void Puzzle09::SolvePartA()
{
    std::cout << "Part A Solution: " << LowPointsRiskLevel() << std::endl;
}

void Puzzle09::SolvePartB()
{
    std::cout << "Part B Solution: " << ThreeLargestBasin() << std::endl;
}

bool Puzzle09::ValidPosition(int i, int j, int m, int n)
{
    if (i >= 0 && i < HeightMap.size() && j >= 0 && j < HeightMap[i].size() && ((i + m) >= 0) && ((j + n) >= 0) &&
        ((i + m) < HeightMap.size()) && ((j + n) < HeightMap[i].size()))
    {
        return true;
    }

    return false;
}

bool Puzzle09::IsBasin(int i, int j)
{
    int Checker = 0;

    for (int m = -1; m <= 1; m++)
    {
        for (int n = -1; n <= 1; n++)
        {
            if (ValidPosition(i, j, m, n))
            {
                if (HeightMap[i][j] > HeightMap[i + m][j + n])
                    Checker++;
            }
        }
    }

    if (Checker == 0)
        return true;
    return false;
}

int Puzzle09::LowPointsRiskLevel()
{
    int Count = 0;

    for (int i = 0; i < HeightMap.size(); i++)
    {
        for (int j = 0; j < HeightMap[i].size(); j++)
        {
            if (IsBasin(i, j))
                Count += (1 + HeightMap[i][j]);
        }
    }
    return Count;
}

int Puzzle09::GetBasinSize(int i, int j)
{
    // use 5 as an example, location 2,2
    // need to go to
    //
    // 1,1 , 1,2 , 1,3
    // 2,1 ,       2,3
    // 3,1 , 3,2 , 3,3
    //
    // i-1,j-1 , i-1,j , i-1,j+1
    // i  ,j-1 , i  ,j   i  ,j+1
    // i+1,j-1 , i+1,j , i+1,j+1

    int Count = 0;

    // go to every direction to see if we can add + 1
    for (int m = -1; m <= 1; m++)
    {
        for (int n = -1; n <= 1; n++)
        {
            if (ValidPosition(i, j, m, n))
            {
                if (HeightMap[i + m][j + n] - HeightMap[i][j] == 1 && HeightMap[i + m][j + n] != 9 &&
                    !HeightMapChecker[i + m][j + n])
                {
                    HeightMapChecker[i + m][j + n] = true;
                    Count += 1 + GetBasinSize((i + m), (j + n));
                }
            }
        }
    }

    return Count;
}

int Puzzle09::ThreeLargestBasin()
{
    std::vector<int> Basins;

    for (int i = 0; i < HeightMap.size(); i++)
    {
        for (int j = 0; j < HeightMap[i].size(); j++)
        {
            // find out if location i, j is a basin
            // it is being double counted
            ResetChecker();
            HeightMapChecker[i][j] = true;
            if (IsBasin(i, j))
                Basins.push_back(1 + GetBasinSize(i, j));
        }
    }

    std::sort(Basins.begin(), Basins.end(), std::greater<>());

    int ReturnValue = 1;
    if (Basins.size() >= 3)
    {
        for (int i = 0; i < 3; i++)
            ReturnValue *= Basins[i];
        return ReturnValue;
    }

    return ReturnValue;
}
