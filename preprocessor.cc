/*
    Run this to make a word file with five letter words and no special characters, 
    using dict-words.txt as a base.
*/

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using std::string;

const string inputFile{"dict-words.txt"};
const string outputFile{"fiveLetterWords.txt"};

int main () {

    std::ifstream input(inputFile);

    std::regex req("^[a-zA-Z]{5}$"); //Five letter words containing only letters A-Z, big or small.
    string word;

    while(input >> word) {
        if(std::regex_match(word, req)) {
            //Turn to lower case

            //Add to output file
        }
    }


    
}