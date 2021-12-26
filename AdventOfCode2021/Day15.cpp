#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Looks like a dfs problem?
 * Cannot move diagonally
 */

std::vector<std::string> read_lines_in_file(const std::__fs::filesystem::path &path)
{
    assert(std::__fs::filesystem::exists(path));

    std::vector<std::string> all_lines;
    std::ifstream file_stream(path);
    std::string current_line;

    while (getline(file_stream, current_line))
    {
        all_lines.push_back(current_line);
    }

    return all_lines;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> input = read_lines_in_file("Day15.txt");

    return 0;
}