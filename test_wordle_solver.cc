#include "wordle_solver.h"
#include <cassert>
#include <iostream>
#include <algorithm>


bool test_contains();

int main() {
    std::cout << std::boolalpha;
    std::cout << test_contains() << "\n"; 
}

//If assert is true, the program continue
bool test_contains()
{
    std::string word_first = "abcde";
    std::string word_second = "efghi";

    assert(contains_any_of(word_first, word_second));
    assert(!contains_any_of("", word_second)); // False: empty string
    assert(contains_any_of(word_first, "bghjt")); //True, b is in the word
    assert(contains_any_of(word_first, "")); //True, no letters are forbidden

    assert(contains_at(word_first, 'a', 0)); //True
    assert(!contains_at(word_first, 'a', 1)); //False: Contains 'a' but wrong position
    assert(!contains_at(word_first, 'z', 0)); // False: 'z' doesn't exist

    assert(contains_but_not_at(word_first, 'a', 2)); //True
    assert(!contains_but_not_at(word_first, 'a', 0)); //False: Contains 'a' but on correct position
    assert(!contains_but_not_at(word_first, 'f', 3)); //False: Doesn't contain 'f' at all.

    //TEST correct_fn
    letters_and_indices correct;
    correct.insert(wordpair(1, "a"));
    correct.insert(wordpair(2, "b"));
    correct_fn cfn{correct};

    assert(cfn("cabf"));
    assert(!cfn("acfb"));

    //TEST misplaced_fn
    letters_and_indices misplaced;
    misplaced.insert(wordpair(0, "abc"));
    misplaced.insert(wordpair(1, "g"));
    misplaced_fn mfn(misplaced);

    assert(mfn("habcg")); //TRUE: cd är med, på andra platser än noterat
    assert(!mfn("habcf")); //FALSE: g is not in the word at all
    assert(!mfn("abcgh")); //FALSE: a is in the given index

    //TEST invalid_letters
    invalid_letters_fn inv{"abcdegf"};
    invalid_letters_fn no_grey("");

    assert(inv("hijkl")); //TRUE, all letters are not grey
    assert(!inv("ahjbc")); //FALSE, some letters are grey
    assert(!inv("afgde")); //FALSE, all letters gray, different indexes
    assert(no_grey("abcde")); //If no grey, all should pass

    std::vector<std::string> wordlist{getFiveLetterWords()};
    std::string wrongLetters{"crtin"};
    letters_and_indices correctLetters;
    correctLetters.insert(wordpair(0, "a"));
    correctLetters.insert(wordpair(1, "l"));
    correctLetters.insert(wordpair(3, "e"));
    letters_and_indices misplaceLetters;
    misplaceLetters.insert(wordpair(0, "l"));
    misplaceLetters.insert(wordpair(1, "e"));
    misplaceLetters.insert(wordpair(4, "a"));
    exclude_word excl(wrongLetters, correctLetters, misplaceLetters);
    
    wordlist.erase(std::remove_if(wordlist.begin(), wordlist.end(), excl), wordlist.end());

#if 1
    for(string s : wordlist) {
        std::cout << s << std::endl;
    }
#endif
    
    //TODO: Should there be a case when false is returned? Test always pass if all assert pass.
    return true;
}