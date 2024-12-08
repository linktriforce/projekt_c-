#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include "wordle_solver.h"

/**
 * Check for gray tiles
 * @returns true if the string s contains any of the characters in the string char_set,
 */
bool wordle_solver::contains_any_of(const string &s, const string &char_set)
{
    if (s.length() != 5 || char_set.length() != 5)
        return false;

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
bool wordle_solver::contains_at(const string &s, char c, size_type pos)
{
    return s.find(c) == pos;
}

/**
 * Check for yellow tiles
 * @return return true if string s contains c but at any other position than pos,
 */
bool wordle_solver::contains_but_not_at(const string &s, char c, size_type pos)
{
    // If c exist in s and it in the wrong pos
    return s.find(c) != string::npos && s.find(c) != pos;
}