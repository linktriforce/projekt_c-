#include <iostream>
#include <string>
#include <algorithm> // For std::find, std::any_of


#include "wordle_solver.h"

/**
 * Gray tile
 * @returns true if the string s contains any of the characters in cs,
 */
bool wordle_solver::contains_any_of(const std::string& s, const std::string& cs) {
    if (s.length() != 5 || cs.length() != 5) return false;
    
    for (char c : cs) {
        if (s.find(c) != std::string::npos) {
            return true;
        }
    }
    return false;
} 

/**
 * Green tile
 * @return true if the string s has the character c at position pos
 */ 
bool wordle_solver::contains_at(const std::string& s, char c, string::size_type pos) {
    return s.find(c) == pos;
}

/**
 * Yellow
 * @return return true if string s contains c but at any other position than pos,
 */
bool wordle_solver::contains_but_not_at(const std::string& s, char c, string::size_type pos) {
    //Om char finns i string och den ligger på fel ställe
    return s.find(c) != std::string::npos && s.find(c) != pos;
}