#include "Utilities.cpp"
#include <array>
#include <iostream>
#include <vector>

/**
 * 0: a, b, c, e, f, g     - 6
 * 1: c, f                 - 2 <-
 * 2: a, c, d e, g         - 5
 * 3: a, c, d, f, g        - 5
 * 4: b, c, d, f           - 4 <-
 * 5: a, b, d, f, g        - 5
 * 6: a, b, d, e, f, g     - 6
 * 7: a, c, f              - 3 <-
 * 8: a, b, c, d, e, f, g  - 7 <-
 * 9: a, b, c, d, f, g     - 6
 */

struct Entry
{
    std::array<std::string, 10> Signal;
    std::array<std::string, 4> Output;
};

struct Display
{
    std::array<std::string, 7> LetterCode;
    std::array<bool, 7> Switch{};
};

class Puzzle08
{
  private:
    std::vector<std::string> Input;
    std::vector<Entry> Entries;
    std::array<std::vector<char>, 10> Schema;
    std::array<Display, 10> DisplaySettings;

  public:
    Puzzle08();
    void SolvePartA();
    void SolvePartB();
    int GetUniqueOutputSegmentNumber();
};

Puzzle08::Puzzle08()
{
    Input = Utilities::ReadAllLinesInFile("Puzzle08.txt");
    for (const std::string &InputLine : Input)
    {
        std::vector<std::string> InputSplit = Utilities::Split(InputLine, " | ");
        std::vector<std::string> SignalSplit = Utilities::Split(InputSplit[0], " ");
        std::vector<std::string> OutputSplit = Utilities::Split(InputSplit[1], " ");

        assert(SignalSplit.size() == 10);
        assert(OutputSplit.size() == 4);

        Entry NewEntry;
        for (int i = 0; i < SignalSplit.size(); i++)
            NewEntry.Signal[i] = SignalSplit[i];
        for (int i = 0; i < OutputSplit.size(); i++)
            NewEntry.Output[i] = OutputSplit[i];

        Entries.push_back(NewEntry);
    }

    Schema[0] = {'a', 'b', 'c', 'e', 'f', 'g'};
    Schema[1] = {'c', 'f'};
    Schema[2] = {'a', 'c', 'd', 'e', 'g'};
    Schema[3] = {'a', 'c', 'd', 'f', 'g'};
    Schema[4] = {'b', 'c', 'd', 'f'};
    Schema[5] = {'a', 'b', 'd', 'f', 'g'};
    Schema[6] = {'a', 'b', 'd', 'e', 'f', 'g'};
    Schema[7] = {'a', 'c', 'f'};
    Schema[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    Schema[9] = {'a', 'b', 'c', 'd', 'f', 'g'};
}

void Puzzle08::SolvePartA()
{
    std::cout << "Part A Solution: " << GetUniqueOutputSegmentNumber() << std::endl;
}

void Puzzle08::SolvePartB()
{
    std::cout << "Part B Solution: " << std::endl;
}

int Puzzle08::GetUniqueOutputSegmentNumber()
{
    int Count = 0;
    for (const Entry &CurrentEntry : Entries)
    {
        for (const std::string &CurrentOutput : CurrentEntry.Output)
        {
            if (CurrentOutput.size() == Schema[1].size() || CurrentOutput.size() == Schema[4].size() ||
                CurrentOutput.size() == Schema[7].size() || CurrentOutput.size() == Schema[8].size())
            {
                Count++;
            }
        }
    }
    return Count;
}