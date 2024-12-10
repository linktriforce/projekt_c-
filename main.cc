#include "filters.h"
#include "input_handler.h"

using std::string;

int main()
{
    //Get word list from file from user input path
    std::vector<string> possible_words{promptFileName()};
    
    do
    {
        //Get user input and filter possible_words
        auto tiles = prompt();
        exclude_word_fn o(std::get<0>(tiles), std::get<1>(tiles), std::get<2>(tiles));
        possible_words.erase(std::remove_if(possible_words.begin(), possible_words.end(), o), possible_words.end());

        if (possible_words.size() == 0)
        {
            std::cout << "No suggestions left for solutions. Program terminating.";
            break;
        }

        for (string w : possible_words)
        {
            std::cout << w << "\n";
        }
    } while (anotherIteration()); //Ask if user wants to continue

    return 0;
}