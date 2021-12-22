#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

static const int bits = 12;

class Utilities
{
  public:
    static std::vector<std::string> ReadLines(const std::__fs::filesystem::path &Path);
    static int GetFirstLineLength(const std::__fs::filesystem::path &Path);
    static std::vector<std::bitset<bits>> ConvertToBitset(const std::vector<std::string> &Strings);
    static std::vector<std::string> Split(const std::string &s, const std::string &delimiter);
    static std::vector<int> ConvertToInt(const std::vector<std::string> &Vec);
    static void VerifyElseCrash(bool bAssert);
    static void VerifyNotReached();
    static std::vector<int> GetBoardRow(const std::string &basicString);
};

std::vector<std::string> Utilities::ReadLines(const std::__fs::filesystem::path &Path)
{
    // crash the program if the file doesn't exist
    VerifyElseCrash(std::__fs::filesystem::exists(Path));

    std::vector<std::string> AllLines;
    std::ifstream FileStream(Path);
    std::string CurrentLine;

    while (std::getline(FileStream, CurrentLine))
    {
        AllLines.push_back(CurrentLine);
    }

    return AllLines;
}

std::vector<std::string> Utilities::Split(const std::string &s, const std::string &delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));

    return res;
}

std::vector<std::bitset<bits>> Utilities::ConvertToBitset(const std::vector<std::string> &Strings)
{
    std::vector<std::bitset<bits>> Bitsets;
    Bitsets.reserve(Strings.size());
    for (const std::string &StringBytes : Strings)
    {
        Bitsets.emplace_back(StringBytes);
    }
    return Bitsets;
}

void Utilities::VerifyElseCrash(bool bAssert)
{
    assert(bAssert);
    if (!bAssert)
    {
        std::terminate();
    }
}

void Utilities::VerifyNotReached()
{
    VerifyElseCrash(false);
}

std::vector<int> Utilities::ConvertToInt(const std::vector<std::string> &Vec)
{
    std::vector<int> ReturnVec;
    ReturnVec.reserve(Vec.size());
    for (const std::string &Str : Vec)
    {
        ReturnVec.push_back(std::stoi(Str));
    }

    return ReturnVec;
}

std::vector<int> Utilities::GetBoardRow(const std::string &BasicString)
{
    std::vector<int> ReturnVec;
    const int slots = 14;

    for (int i = 1; i <= slots; i++)
    {
        std::string Number = BasicString.substr(i - 1, i + 1);
        if (i % 3 == 1)
            ReturnVec.push_back(stoi(Number));
    }

    return ReturnVec;
}
int Utilities::GetFirstLineLength(const std::__fs::filesystem::path &Path)
{
    VerifyElseCrash(std::__fs::filesystem::exists(Path));

    std::vector<std::string> FirstLine;
    std::ifstream FileStream(Path);
    std::string CurrentLine;

    std::getline(FileStream, CurrentLine);
    FirstLine.push_back(CurrentLine);

    return (int)FirstLine[0].size();
}
