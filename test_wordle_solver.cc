#include "wordle_solver.h"
#include <cassert>
#include <iostream>


bool test_contains();

int main() {
    std::cout << test_contains() << "\n"; 
}

//If assert is true, the program continue
bool test_contains()
{
    std::string word_first = "abcde";
    std::string word_second = "efghi";

    assert(contains_any_of(word_first, word_second));
    assert(!contains_any_of("", word_second)); // False: empty string

    assert(contains_at(word_first, 'a', 0)); //True
    assert(!contains_at(word_first, 'a', 1)); //False: Contains 'a' but wrong position
    assert(!contains_at(word_first, 'z', 0)); // False: 'z' doesn't exist

    assert(contains_but_not_at(word_first, 'a', 2)); //True
    assert(!contains_but_not_at(word_first, 'a', 0)); //False: Contains 'a' but on correct position

    //TODO: Should there be a case when false is returned? Test always pass if all assert pass.
    return true;
}