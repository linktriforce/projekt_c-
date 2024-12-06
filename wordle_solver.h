#ifndef WORDLE_SOLVER_H_
#define WORDLE_SOLVER_H_

#include <string>
#include <regex>

using std::string;

class wordle_solver {

public:
    bool contains_any_of(const string& s, const string& cs);
    bool contains_at(const string& s, char c, string::size_type pos);
    bool contains_but_not_at(const string& s, char c, string::size_type pos);
private:

};  

#endif