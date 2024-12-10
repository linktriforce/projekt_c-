#include "input_handler.h"
#include "filters.h"

void toLowerCase(std::string &s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                   { return std::tolower(c); });
}

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
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                           { return std::tolower(c); });

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
        std::cout << "Would you like to continue cheating? (y/n)" << std::endl;
        std::cin >> keepCheating;
    } while (keepCheating != "y" && keepCheating != "n");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return keepCheating == "y";
}

std::tuple<std::string, letters_and_indices, letters_and_indices> prompt()
{
    std::string wrong;
    std::cout << "enter wrong letters:\n";
    std::getline(std::cin, wrong);
    toLowerCase(wrong);

    std::string correct;
    std::cout << "enter correct letters (letter index)* e.g '2 c 3 d':\n";
    std::getline(std::cin, correct);
    toLowerCase(correct);
    auto corr = build_list(correct);

    std::string misplaced;
    std::cout << "enter misplaced letters (letter index)* e.g '0 p 0 r':\n";
    std::getline(std::cin, misplaced);
    toLowerCase(misplaced);
    auto misp = build_list(misplaced);

    return {wrong, corr, misp};
}

std::vector<std::string> promptFileName() {
    std::cout << "Enter path to word list file (press Enter to use default list): " << std::endl;
    string inputFile;
    std::getline(std::cin, inputFile);

    if(inputFile == "") {
        inputFile = defaultTextFile;
    }

    std::vector<string> possible_words{getFiveLetterWords(inputFile)};
    return possible_words;
}