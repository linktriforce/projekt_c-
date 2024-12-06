#include "wordle_solver.h"
#include <cassert>
#include <iostream>


//If assert is true, the program continue
bool test_contains()
{
    wordle_solver ws;
    std::string word_first = "abcde";
    std::string word_second = "efghi";

    assert(ws.contains_any_of(word_first, word_second));
    assert(!ws.contains_any_of("", word_second)); // False: empty string

    assert(ws.contains_at(word_first, 'a', 0)); //True
    assert(!ws.contains_at(word_first, 'a', 1)); //False: Contains 'a' but wrong position
    assert(!ws.contains_at(word_first, 'z', 0)); // False: 'z' doesn't exist

    assert(ws.contains_but_not_at(word_first, 'a', 2)); //True
    assert(!ws.contains_but_not_at(word_first, 'a', 0)); //False: Contains 'a' but on correct position

    //TODO: Should there be a case when false is returned? Test always pass if all assert pass.
    return true;
}

int main()
{
    if (test_contains()) std::cout << "Test passed!";
    
    return 0;
}