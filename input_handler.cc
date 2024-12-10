#include "input_handler.h"

void toLowerCase(std::string &s)
{
    std::getline(std::cin, s);
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                   { return std::tolower(c); });
}

/**
 * Reads the file and finds all five letter words
 * @return std::vector<std::string> containing five letter words
 */
std::vector<std::string> getFiveLetterWords(const string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "File '" << filename << "' does not exist";
    }

    std::string word;
    std::vector<std::string> fiveLetterWords;

    std::regex req("^[a-zA-Z]{5}$");

    while (file >> word)
    {
        if (std::regex_match(word, req))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { 
                return std::tolower(c); 
            });

            fiveLetterWords.push_back(word);
        }
    }
    
    return fiveLetterWords;
}

bool anotherIteration()
{
    std::string keepCheating;
    do
    {
                keepCheating.clear();

        std::cout << "Would you like to continue cheating? (y/n)\n";
        std::getline(std::cin, keepCheating);
        toLowerCase(keepCheating);
        std::cout << "Wrong input! Try again.\n";
    } while (keepCheating != "y" && keepCheating != "n");

            return keepCheating == "y";
}

letters_and_indices build_list(const string &line)
{
    letters_and_indices map;
    std::stringstream ss(line);

    int index;
    while (ss >> index)
    {
        string letter;
        if (ss >> letter)
        {
            map[index] += letter;
        }
    }

    for (const auto &pair : map)
    {
        std::cout << "Index: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return map;
}

std::tuple<std::string, letters_and_indices, letters_and_indices> prompt()
{
    std::string wrong;
    std::cout << "enter wrong letters:\n";
    toLowerCase(wrong);

    std::string correct;
    std::cout << "enter correct letters (letter index)* e.g '2 c 3 d':\n";
    toLowerCase(correct);
    auto corr = build_list(correct);

    std::string misplaced;
    std::cout << "enter misplaced letters (letter index)* e.g '0 p 0 r':\n";
    toLowerCase(misplaced);
    auto misp = build_list(misplaced);

    return {wrong, corr, misp};
}