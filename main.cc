#include "filters.h"
#include "input_handler.h"

using std::string;

int main()
{
    std::vector<string> possible_words{promptFileName()};
    
    do
    {
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
    } while (anotherIteration());
    return 0;
}