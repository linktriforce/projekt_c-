#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "wordle_solver.h"

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;

const string inputFile = "textfiles/fiveLetterWords.txt";

void handleGreenTiles(letters_and_indices &greenTiles)
{
    string green;
    std::getline(std::cin, green);

    std::stringstream ss(green);
    
    int index;
    while (ss)
    {
        if (ss >> index)
        {
            std::cout << index;
            ss.ignore(); // skip space
            char letter[2];
            if (ss >> letter)
            {
                std::cout << letter;
                greenTiles.insert({index, string(letter)}); // Type conversion. Safe?
            }
            ss.ignore(); // skip space
        }
    }
}

void handleYellowTiles(letters_and_indices &yellowTiles)
{
    int index;
    string yellow;
    std::cin >> yellow;
    std::stringstream ss(yellow);
    while (ss)
    {
        int index;
        if (ss >> index)
        {
            ss.ignore(); // skip space
            char n[50];
            if (ss >> n)
            {
                yellowTiles.insert({index, string(n)}); // Type conversion. Safe?
            }
            ss.ignore(); // skip space
        }
    }
}

int main()
{
    // Handle gray tiles
    std::ifstream input(inputFile);
    string gray;
    std::cout << "Enter gray tiles: ";
    std::cin >> gray;

    // Handle green tiles
    std::cout << "Enter green tiles (e.g format: '2 c 3 d'): ";
    letters_and_indices greenTiles;
    handleGreenTiles(greenTiles);

    for (const auto &pair : greenTiles)
    {
        std::cout << "Index: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    // Handle yellow tiles
    string yellow;
    std::cout << "Enter yellow tiles (e.g format: 4 efg): ";
    std::cin >> yellow;
    letters_and_indices yellowTiles;
    handleYellowTiles(yellowTiles);

    for (const auto &pair : yellowTiles)
    {
        std::cout << "Index: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    // Instanciate functors
    invalid_letters_fn invalid_letters_fn(gray); // user input
    correct_fn correct_fn(greenTiles);           // user input
    misplaced_fn misplaced_fn(yellowTiles);      // user input

    std::set<string> possible_words;

    for (string word; std::getline(input, word);)
    {
        if (invalid_letters_fn(word) && correct_fn(word) && misplaced_fn(word)) // from fiveletterwordlist
        {
            // If not invalid letter add to set of possible words
            std::cout << "Words without the letters '" << gray << "' added to the set";
            possible_words.insert(word);
        }
    }

    // map.insert({0, "a"});
    // map.insert({1, "b"});
    // map.insert({2, "k"});

    // correct_fn correct_fn(map);

    // if (correct_fn("abcde"))
    // {
    //     std::cout << "Doesnt contain a gray letter";
    // }
    // else
    // {
    //     std::cout << "Contains a gray letter\n";
    // }
    return 0;

}