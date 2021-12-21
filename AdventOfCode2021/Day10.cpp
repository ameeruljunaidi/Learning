#include "Utilities.cpp"
#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

class Puzzle10
{
  private:
    static std::vector<std::string> Input;
    static std::unordered_map<char, int> ScoringMapPartA;
    static std::unordered_map<char, int> ScoringMapPartB;
    static std::unordered_map<char, char> Pairs;
    static char OpeningCharacter(char ClosingCharacter);
    static int TotalSyntaxErrorScore();
    static long long TotalScoreMiddle();
    static std::stack<char> GetStack(const std::string &CurrentLine);
    static std::vector<char> ConvertToVector(std::stack<char> &CurrentStack, bool RemoveIncomplete);

  public:
    explicit Puzzle10(const std::string &FileName);
    void SolvePartA();
    void SolvePartB();
};

std::vector<std::string> Puzzle10::Input;
std::unordered_map<char, int> Puzzle10::ScoringMapPartA;
std::unordered_map<char, int> Puzzle10::ScoringMapPartB;
std::unordered_map<char, char> Puzzle10::Pairs;

Puzzle10::Puzzle10(const std::string &FileName)
{
    Input = Utilities::ReadAllLinesInFile(FileName);

    ScoringMapPartA = {
        {')', 3},
        {']', 57},
        {'}', 1197},
        {'>', 25137},
    };

    ScoringMapPartB = {
        {')', 1},
        {']', 2},
        {'}', 3},
        {'>', 4},
    };

    Pairs = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'},
        {'<', '>'},
    };
}

void Puzzle10::SolvePartA()
{
    std::cout << "Part A Solution: " << TotalSyntaxErrorScore() << std::endl;
}

void Puzzle10::SolvePartB()
{
    std::cout << "Part B Solution: " << TotalScoreMiddle() << std::endl;
}

char Puzzle10::OpeningCharacter(char ClosingCharacter)
{
    for (std::pair<char, char> CurrentPair : Pairs)
    {
        if (CurrentPair.second == ClosingCharacter)
            return CurrentPair.first;
    }
    return '0';
}

std::stack<char> Puzzle10::GetStack(const std::string &CurrentLine)
{
    std::stack<char> CurrentStack;
    for (const char &CurrentCharacter : CurrentLine)
    {
        // only add to the stack if the top element  is not equal to the opening char
        if (CurrentStack.empty())
        {
            CurrentStack.push(CurrentCharacter);
            continue;
        }

        if (CurrentStack.top() == OpeningCharacter(CurrentCharacter))
            CurrentStack.pop();
        else
            CurrentStack.push(CurrentCharacter);
    }
    return CurrentStack;
}

int Puzzle10::TotalSyntaxErrorScore()
{
    // need to use the stack data structure
    int Score = 0;

    for (const std::string &CurrentLine : Input)
    {
        // for every line, create a stack and push char by char
        std::stack<char> CurrentStack = GetStack(CurrentLine);

        // store in vector to analyze
        std::vector<char> TempVector = ConvertToVector(CurrentStack, true);

        // score the characters
        for (int i = (int)TempVector.size() - 1; i >= 0; i--)
        {
            if (Pairs[TempVector[i]] == 0)
            {
                Score += ScoringMapPartA[TempVector[i]];
                break;
            }
        }
    }

    return Score;
}

std::vector<char> Puzzle10::ConvertToVector(std::stack<char> &CurrentStack, bool RemoveIncomplete)
{
    std::vector<char> TempVector;
    while (!CurrentStack.empty())
    {
        TempVector.push_back(CurrentStack.top());
        CurrentStack.pop();
    }

    // check if there are any end bracket
    int Checker = 0;
    for (const char &Character : TempVector)
    {
        // there is no pair (it is a closed bracket), add to checker
        if (Pairs[Character] == 0)
        {
            Checker++;
        }
    }

    // if checker is > 0, then there is a close bracket, keep the vector
    if (Checker == 0 && RemoveIncomplete)
    {
        TempVector.clear();
    }

    if (Checker > 0 && !RemoveIncomplete)
    {
        TempVector.clear();
    }

    return TempVector;
}

long long Puzzle10::TotalScoreMiddle()
{
    std::vector<long long> Scores;

    for (const std::string &CurrentLine : Input)
    {
        long long Score = 0;

        // for every line, create a stack and push char by char
        std::stack<char> CurrentStack = GetStack(CurrentLine);

        // convert to vector
        std::vector<char> TempVector = ConvertToVector(CurrentStack, false);

        if (!TempVector.empty())
        {
            for (const char &CurrentCharacter : TempVector)
            {
                Score *= 5;
                long long ToAdd = ScoringMapPartB[Pairs[CurrentCharacter]];
                Score += ToAdd;
            }

            Scores.push_back(Score);
        }
    }

    std::sort(Scores.begin(), Scores.end());

    return Scores[(Scores.size() - 1) / 2];
}