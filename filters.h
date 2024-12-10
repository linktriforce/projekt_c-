#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <regex>
#include <iostream>
#include <fstream>
#include <algorithm>

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;
using wordpair = std::pair<size_type, string>;

/**
 * Check for gray tiles
 * @returns true if the string s contains any of the characters in the string char_set,
 */
bool contains_any_of(const string &s, const string &cs);

/**
 * Check for green tiles
 * @return true if the string s has the character c at position pos
 */
bool contains_at(const string &s, char c, size_type pos);

/**
 * Check for yellow tiles
 * @return return true if string s contains c but at any other position than pos,
 */
bool contains_but_not_at(const string &s, char c, size_type pos);

/**
 * Converts user input to the required data structure used in the filter functors
 * @return letters_and_indices with user input
 */
letters_and_indices build_list(const std::string &line);

struct wrong_fn
{
    wrong_fn(const string &letters) : l{letters} {}

    /**
     * Checks the input word for the letters in wrong_fn
     * @param std::string c to be compared to the letters in the wrong_fn
     * @return true if c contains no letters present in wrong_fn
     */
    bool operator()(const string &c);

private:
    string l;
};

struct correct_fn
{
    correct_fn(const letters_and_indices &idxs) : m{idxs} {}

    /**
     * Compares the input string to the correct_fn's letters_and_indices
     * @param const string &c
     * @return true if all letters of the correct_fn is in the correct place in c
     */
    bool operator()(const string &c);

private:
    letters_and_indices m;
};

struct misplaced_fn
{
    misplaced_fn(const letters_and_indices &idxs) : m{idxs} {}

    /**
     * Compares the input string to the letters_and_indices of the misplaced_fn to looks for misplaced characters
     * @return true if any character of the input string has a correct letter in the wrong place
     */
    bool operator()(const string &c);

private:
    letters_and_indices m;
};

struct exclude_word_fn
{
    exclude_word_fn(const std::string &wrong,
                    const letters_and_indices &correct,
                    const letters_and_indices &misplaced) : w{wrong}, c{correct}, m{misplaced} {};

    /**
     * @return true if the input word fails any of the tests provided by wrong_fn, correc_fn and misplaced_fn
     */
    bool operator()(const std::string &w);

private:
    wrong_fn w;
    correct_fn c;
    misplaced_fn m;
};