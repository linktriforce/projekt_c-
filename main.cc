#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>

#include "wordle_solver.h"

using std::string;

int main()
{
    std::cout << "Enter path to file: " << std::endl;
    string inputFile;
    std::getline(std::cin, inputFile);
    std::vector<string> possible_words{getFiveLetterWords(inputFile)};
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