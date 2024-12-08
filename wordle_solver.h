#ifndef WORDLE_SOLVER_H_
#define WORDLE_SOLVER_H_

#include <string>

using std::string;
using size_type = string::size_type;
using letters_and_indices = std::map<size_type, string>;

class wordle_solver
{

public:
    bool static contains_any_of(const string &s, const string &cs);
    bool contains_at(const string &s, char c, size_type pos);
    bool contains_but_not_at(const string &s, char c, size_type pos);

    struct invalid_letters_fn //osäker på syftet av wrong_fn
    {
        invalid_letters_fn(const string &letters) : l{letters} {}
        bool operator()(const string &c) {
            return !contains_any_of(l, c);
        }

    private:
        string l;
    };

    struct correct_fn
    {
        correct_fn(const letters_and_indices &idxs) : m{idxs} {}
        bool operator()(const string &c);

    private:
        letters_and_indices m;
    };

    struct misplaced_fn
    {
        misplaced_fn(const letters_and_indices &idxs) : m{idxs} {}
        bool operator()(const string &c);

    private:
        letters_and_indices m;
    };

private:
};

#endif