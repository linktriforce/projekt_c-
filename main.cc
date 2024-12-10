#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>

#include "wordle_solver.h"

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;

bool anotherIteration();

letters_and_indices build_list(const std::string &line)
{
    letters_and_indices map;
    std::stringstream ss(line);

    int index;
    while (ss >> index)
    {
        // ss.ignore(); // skip space
        string letter;
        if (ss >> letter)
        {
            map[index] += letter;
            // if (map.find(index) != map.end())
            // {
            //     map.at(index).append(letter);
            // }
            // else
            // {
            //     map.insert({index, letter});
            // }
        }
        // ss.ignore(); // skip space
    }

    for (const auto &pair : map)
    {
        std::cout << "Index: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return map;
}

void toLowerCase(std::string &s)
{
    std::getline(std::cin, s);
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                   { return std::tolower(c); });
}

std::tuple<std::string, letters_and_indices, letters_and_indices> prompt()
{
    std::string wrong;
    std::cout << "enter wrong letters:\n";
    toLowerCase(wrong);

    std::string correct;
    std::cout << "enter correct letters (letter index)* e.g '2 c 3 d':\n";
    toLowerCase(correct);
    auto corr = build_list(correct);

    std::string misplaced;
    std::cout << "enter misplaced letters (letter index)* e.g '0 p 0 r':\n";
    toLowerCase(misplaced);
    auto misp = build_list(misplaced);

    return {wrong, corr, misp};
}

int main()
{
    std::vector<string> possible_words(getFiveLetterWords());
    do
    {
        auto tiles = prompt();
        exclude_word_fn o(std::get<0>(tiles), std::get<1>(tiles), std::get<2>(tiles));
        possible_words.erase(std::remove_if(possible_words.begin(), possible_words.end(), o), possible_words.end());

        if (possible_words.size() == 0)
        {
            std::cout << "No suggestions left for solutions. Program terminating.";
            break;
        }

        for (string w : possible_words)
        {
            std::cout << w << "\n";
        }
    } while (anotherIteration());
    return 0;
}

bool anotherIteration()
{
    std::string keepCheating;
    std::cout << "Would you like to continue cheating? (y/n)\n";
    std::getline(std::cin, keepCheating);
            toLowerCase(keepCheating);


    while (keepCheating != "y" && keepCheating != "n")
    {
        std::cout << "Wrong input! Try again.\n";
        std::cout << "Would you like to continue cheating? (y/n)\n";
        std::getline(std::cin, keepCheating);
    }

    return keepCheating == "y";
}
