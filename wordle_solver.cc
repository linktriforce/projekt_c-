#include <iostream>
#include <fstream>
#include <algorithm>

#include "wordle_solver.h"

/**
 * Turns the fiveLetterWords.txt and turns in into a vector of strings
 * @return std::vector<std::string> containing the five letter words
 */
std::vector<std::string> getFiveLetterWords() {
    std::ifstream file("textfiles/fiveLetterWords.txt");
    std::string word;
    std::vector<std::string> fiveLetterWords;

    while(file >> word) {
        fiveLetterWords.push_back(word);
    }

    return fiveLetterWords;
}

/**
 * Check for gray tiles
 * @returns true if the string s contains any of the characters in the string char_set,
 */
bool contains_any_of(const string &s, const string &char_set)
{
    if(char_set.length() == 0) {
        return true;
    }

    for (char c : char_set)
    {
        if (s.find(c) != string::npos)
        {
            return true;
        }
    }
    return false;
}

/**
 * Check for green tiles
 * @return true if the string s has the character c at position pos
 */
bool contains_at(const string &s, char c, size_type pos)
{
    return s[pos] == c;
}

/**
 * Check for yellow tiles
 * @return return true if string s contains c but at any other position than pos,
 */
bool contains_but_not_at(const string &s, char c, size_type pos)
{
    // If c exist in s and it in the wrong pos
    return s.find(c) != string::npos && s.find(c) != pos;
}

bool invalid_letters_fn::operator() (const string &c) {
    if (l.length() > 0) {
        return !contains_any_of(c, l);
    } else {
        return true;
    }
}

bool correct_fn::operator() (const string &c) {
    return std::all_of(m.begin(), m.end(), [c](std::pair<size_type, string> p) {
        return contains_at(c, p.second[0], p.first);
    });
}

bool misplaced_fn::operator() (const string &c) {
    //För varje ordpar
    for(wordpair wp : m) {
        for(char ch : wp.second) {
            //Om någon bokstav returnerar true, sätt till true
            if(!contains_but_not_at(c, ch, wp.first)) {
                return false;
            }
        }      
    }
    return true;
}

bool exclude_word::operator() (const string &word) {
    return !(w(word) && c(word) && m(word));    
}