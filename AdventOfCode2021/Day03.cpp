#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "LocalValueEscapesScope"

#include "Utilities.cpp"
#include <array>
#include <bitset>
#include <iostream>
#include <vector>

class Puzzle03
{
  public:
    Puzzle03();
    void SolvePartA();
    void SolvePartB();

  private:
    std::vector<std::string> DiagnosticsString;
    std::vector<std::bitset<bits>> Diagnostics;
    int GetGammaEpsilon(const std::string &Type);
    int GetOxygenCO2(const std::string &Type);
};

Puzzle03::Puzzle03()
{
    DiagnosticsString = Utilities::ReadAllLinesInFile("Puzzle03.txt");
    Diagnostics = Utilities::ConvertToBitset(DiagnosticsString);
}

void Puzzle03::SolvePartA()
{
    std::cout << "Part A Solution" << std::endl;
    std::cout << "Gamma Rate: " << GetGammaEpsilon("Gamma") << std::endl;
    std::cout << "Epsilon Rate: " << GetGammaEpsilon("Epsilon") << std::endl;
    std::cout << "Answer Part A: " << GetGammaEpsilon("Gamma") * GetGammaEpsilon("Epsilon") << std::endl;
    std::cout << std::endl;
}

void Puzzle03::SolvePartB()
{
    std::cout << "Part B Solution" << std::endl;
    std::cout << "Oxygen Rate: " << GetOxygenCO2("Oxygen") << std::endl;
    std::cout << "CO2 Rate: " << GetOxygenCO2("CO2") << std::endl;
    std::cout << "Answer Part A: " << GetOxygenCO2("Oxygen") * GetOxygenCO2("CO2") << std::endl;
    std::cout << std::endl;
}

int Puzzle03::GetGammaEpsilon(const std::string &Type)
{
    std::bitset<bits> GammaRateBits;
    for (int i = 0; i < bits; i++)
    {
        std::array<int, 2> MostCommon = {0, 0};
        for (std::bitset<bits> Bitset : Diagnostics)
        {
            MostCommon[Bitset[i]]++;
        }
        GammaRateBits[i] = MostCommon[1] > MostCommon[0];
    }

    if (Type == "Gamma")
    {
        return (int)GammaRateBits.to_ulong();
    }
    else if (Type == "Epsilon")
    {
        return (int)GammaRateBits.flip().to_ulong();
    }
    return -1;
}

int Puzzle03::GetOxygenCO2(const std::string &Type)
{
    // initialize variables for oxygen rate and co2 rate
    std::bitset<bits> OxygenRate, CO2Rate;

    // create a vector for most common
    std::vector<std::bitset<bits>> MostCommon(Diagnostics);
    // loop through the bits one by one till 12
    for (int i = bits - 1; i >= 0 && MostCommon.size() > 1; i--)
    {
        // create an array of two different vectors
        std::array<std::vector<std::bitset<bits>>, 2> Filtered;
        for (std::bitset<bits> Bitset : MostCommon)
        {
            Filtered[Bitset[i]].push_back(Bitset);
        }
        MostCommon = Filtered[0].size() > Filtered[1].size() ? Filtered[0] : Filtered[1];
    }
    OxygenRate = MostCommon[0];

    // create a vector for least common
    std::vector<std::bitset<bits>> LeastCommon(Diagnostics);
    // loop through the bits one by one till 12
    for (int i = bits - 1; i >= 0 && LeastCommon.size() > 1; i--)
    {
        // create an array of two different vectors
        std::array<std::vector<std::bitset<bits>>, 2> Filtered;
        for (std::bitset<bits> Bitset : LeastCommon)
        {
            Filtered[Bitset[i]].push_back(Bitset);
        }
        LeastCommon = Filtered[0].size() > Filtered[1].size() ? Filtered[1] : Filtered[0];
    }
    CO2Rate = LeastCommon[0];

    if (Type == "Oxygen")
    {
        return (int)OxygenRate.to_ulong();
    }
    else if (Type == "CO2")
    {
        return (int)CO2Rate.to_ulong();
    }

    return -1;
}

#pragma clang diagnostic pop