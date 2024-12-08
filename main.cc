#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include "wordle_solver.h"

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;

const string inputFile = "/fiveLetterWords.txt";

int main()
{
    std::ifstream input(inputFile);
    wordle_solver solver;
    wordle_solver::invalid_letters_fn invalid_letters_fn("abcde"); //wrong_fn
    if (invalid_letters_fn("ghija"))                     
    {
        std::cout << "Doesnt contain a gray letter";
    }
    else
    {
        std::cout << "Contains a gray letter\n";
    }
}