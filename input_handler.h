#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <regex>

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;

const std::string defaultTextFile = "dict-words.txt";

/**
 * Asks the user to input the path to the word list file they would like to use
 * @return std::vector<std::string> containing the five letter words from the given word list file path.
 */
std::vector<std::string> promptFileName();

/**
 * Transforms the input string to lower case
 * @param std::string to be set to lower case
 */
void toLowerCase(std::string &s);

/**
 * Reads the file and finds all five letter words
 * @return std::vector<std::string> containing five letter words
 */
std::vector<std::string> getFiveLetterWords(const string& filename);

/**
 * Asks the user whether it wants to continue or not
 * @return true if the user answers 'y'
 */
bool anotherIteration();

/**
 * Asks the users what letters are wrong, correct and misplaced
 * @return std::tuple<std::string, letters_and_indices, letters_and_indices> with the answers from the user.
 */
std::tuple<std::string, letters_and_indices, letters_and_indices> prompt();