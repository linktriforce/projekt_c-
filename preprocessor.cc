/*
    Run this to make a word file with five letter words and no special characters,
    using dict-words.txt as a base.
*/

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <algorithm>
#include <set>

using std::string;

const string inputFile{"textfiles/dict-words.txt"};
const string outputFile{"textfiles/fiveLetterWords.txt"};

int main()
{

    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    std::regex req("^[a-zA-Z]{5}$"); // Five letter words containing only letters A-Z, big or small.
    string word;
    std::set<string> s;
    while (input >> word)
    {
        if (std::regex_match(word, req))
        {
            // Turn to lower case
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                           { return std::tolower(c); });

            //Ensure no duplicates get written into output
            if(s.find(word) == s.end()) {
                s.insert(word);
                output << word << "\n";
            }
        }
    }
}
