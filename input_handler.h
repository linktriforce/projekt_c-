#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <regex>

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;

void toLowerCase(std::string &s);
std::vector<std::string> getFiveLetterWords(const string& filename);
bool anotherIteration();
std::tuple<std::string, letters_and_indices, letters_and_indices> prompt();