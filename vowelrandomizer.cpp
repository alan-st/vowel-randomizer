#include <algorithm>
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

char randomize_vowel(char c, std::random_device &rd)
{
    const std::string vowels("aeiou");
    std::string::size_type c_pos = vowels.find_first_of(c);
    if (c_pos == std::string::npos) {
        return c;
    }

    std::string vowels_replaced(vowels);
    vowels_replaced.erase(c_pos, 1);

    std::mt19937 gen(rd());
    std::shuffle(vowels_replaced.begin(), vowels_replaced.end(), gen);
    return vowels_replaced[0];
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "Incorrect number of arguments, need filename." << std::endl;
        return -1;
    }

    std::ifstream inp(argv[1]);
    std::vector<std::string> lines;
    if (inp.is_open()) {
        std::string line;
        while (std::getline(inp, line)) {
            lines.push_back(line + '\n');
        }
        inp.close();
    } else {
        std::cout << "Cannot find file '" << argv[1] << "'" << std::endl;
        return -1;
    }

    std::random_device rd;
    for (std::string &line : lines) {
        std::transform(line.begin(), line.end(), line.begin(), [&rd](char c)
                                            {return randomize_vowel(c, rd);});
    }

    std::ofstream out("output.txt");
    for (auto it = lines.cbegin(); it != lines.cend(); ++it) {
        out << *it;
    }
    out.close();
    return 0;
}