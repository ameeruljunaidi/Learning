#include "Utilities.cpp"
#include <iostream>
#include <vector>

struct Board
{
    int WinOrder;
    int LastCalled;
    std::vector<std::vector<int>> Numbers;
    std::vector<std::vector<int>> Checkers;
};

class Puzzle04
{

  public:
    Puzzle04();
    void SolvePartA();
    void SolvePartB();
    void PrintBoard(const Board &CurrBoard);
    void PrintBoards();
    bool CheckBoard(Board CurrBoard);
    void MarkBoard(int BoardNumber, int &CalledNumber, Board *CurrBoard);
    void MarkBoards();
    void SetChecker(int BoardNumber, int RowNumber, int ColumnNumber, int Value);
    int GetAnswer(Board CurrBoard);

  private:
    std::vector<int> CalledNumbers;
    std::vector<Board> Boards;
    void SortBoards();
    void Initialize();
};

Puzzle04::Puzzle04()
{
    Initialize();
    MarkBoards();
    SortBoards();
}

void Puzzle04::Initialize()
{
    std::vector<std::string> Input = Utilities::ReadAllLinesInFile("Puzzle04.txt");
    int counter = 0;
    std::vector<std::vector<int>> CurrentBoard;
    for (const std::string &Line : Input)
    {
        counter++;
        if (counter == 1)
        {
            std::vector<std::string> CalledNumberStr = Utilities::Split(Line, ",");
            CalledNumbers = Utilities::ConvertToInt(CalledNumberStr);
        }
        else if (counter > 2)
        {
            if (Line.empty())
            {
                std::vector<std::vector<int>> Checker(CurrentBoard);
                for (int i = 0; i < CurrentBoard.size(); i++)
                {
                    for (int j = 0; j < CurrentBoard.size(); j++)
                    {
                        Checker[i][j] = 0;
                    }
                }

                Board NewBoard;
                NewBoard.WinOrder = 0;
                NewBoard.Numbers = CurrentBoard;
                NewBoard.Checkers = Checker;
                Boards.push_back(NewBoard);
                CurrentBoard.clear();
                Checker.clear();
            }
            else
            {
                std::vector<int> RowNumbersInt = Utilities::GetBoardRow(Line);
                CurrentBoard.push_back(RowNumbersInt);
            }
        }
    }
}

void Puzzle04::SolvePartA()
{
    std::cout << "Part A Solution: " << std::endl;
    std::cout << GetAnswer(Boards.front()) << std::endl;
}

void Puzzle04::SolvePartB()
{
    std::cout << "Part B Solution: " << std::endl;
    std::cout << GetAnswer(Boards.back()) << std::endl;
}

void Puzzle04::PrintBoard(const Board &CurrBoard)
{
    for (const std::vector<int> &Row : CurrBoard.Numbers)
    {
        for (int Number : Row)
        {
            std::cout << Number << " ";
        }
        std::cout << std::endl;
    }
}

void Puzzle04::PrintBoards()
{
    for (const Board &CurrBoard : Boards)
    {
        PrintBoard(CurrBoard);
        std::cout << std::endl;
    }
}

bool Puzzle04::CheckBoard(Board CurrBoard)
{
    int count;
    for (int i = 0; i < CurrBoard.Checkers.size(); i++)
    {
        count = 0;
        for (int j = 0; j < CurrBoard.Checkers.size(); j++)
        {
            if (CurrBoard.Checkers[i][j] == 1)
                count++;
            if (count == 5)
                return true;
        }

        count = 0;
        for (auto &Checker : CurrBoard.Checkers)
        {
            if (Checker[i] == 1)
                count++;
            if (count == 5)
                return true;
        }
    }

    return false;
}

void Puzzle04::MarkBoard(int BoardNumber, int &CalledNumber, Board *CurrBoard)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (CurrBoard->Numbers[i][j] == CalledNumber)
            {
                SetChecker(BoardNumber, i, j, 1);
            }
        }
    }
}

void Puzzle04::MarkBoards()
{
    for (int i = 0; i < CalledNumbers.size(); i++)
    {
        for (int j = 0; j < Boards.size(); j++)
        {
            if (Boards[j].WinOrder == 0)
            {
                // Loop through and mark the board
                MarkBoard(j, CalledNumbers[i], &Boards[j]);

                // Check if  already won
                if (CheckBoard(Boards[j]))
                {
                    Boards[j].WinOrder = i + 1;
                    Boards[j].LastCalled = CalledNumbers[i];
                }
            }
        }
    }
}

void Puzzle04::SetChecker(int BoardNumber, int RowNumber, int ColumnNumber, int Value)
{
    Boards[BoardNumber].Checkers[RowNumber][ColumnNumber] = Value;
}

int Puzzle04::GetAnswer(Board CurrBoard)
{
    int Count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (CurrBoard.Checkers[i][j] == 0)
                Count += CurrBoard.Numbers[i][j];
        }
    }

    return CurrBoard.LastCalled * Count;
}

void Puzzle04::SortBoards()
{
    std::sort(Boards.begin(), Boards.end(),
              [](const Board &Left, const Board &Right) { return Left.WinOrder < Right.WinOrder; });
}
