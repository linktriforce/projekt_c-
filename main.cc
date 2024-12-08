#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include "wordle_solver.h"

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;

letters_and_indices build_list(const std::string &line)
{
    letters_and_indices map;
    std::stringstream ss(line);

    int index;
    while (ss)
    {
        if (ss >> index)
        {
            ss.ignore(); // skip space
            string letter;
            if (ss >> letter)
            {
                if (map.find(index) != map.end())
                {
                    map.at(index).append(letter);
                }
                else
                {
                    map.insert({index, letter});
                }
            }
            ss.ignore(); // skip space
        }
    }

    for (const auto &pair : map)
    {
        std::cout << "Index: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return map;
}

std::tuple<std::string, letters_and_indices, letters_and_indices> prompt()
{
    std::string wrong;
    std::cout << "enter wrong letters:\n";
    std::getline(std::cin, wrong);

    std::string correct;
    std::cout << "enter correct letters (letter index)* e.g '2 c 3 d':\n";
    std::getline(std::cin, correct);
    auto corr = build_list(correct);

    std::string misplaced;
    std::cout << "enter misplaced letters (letter index)* e.g '0 p 0 r':\n";
    std::getline(std::cin, misplaced);
    auto misp = build_list(misplaced);

    return {wrong, corr, misp};
}

const string inputFile = "textfiles/fiveLetterWords.txt";

int main()
{
    auto tiles = prompt();
    exclude_word o(std::get<0>(tiles), std::get<1>(tiles), std::get<2>(tiles));
    std::vector<string> possible_words(getFiveLetterWords());
    possible_words.erase(std::remove_if(possible_words.begin(), possible_words.end(), o), possible_words.end());
    for (string w : possible_words) {
        std::cout << w << "\n";
    }
    return 0;
}