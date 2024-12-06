#include <iostream>
#include <string>
#include "wordle_solver.h"

int main () {
    string s = "abcdefghijkolmop";
    string cs = "qa";

    wordle_solver ws;
    if (ws.contains_any_of(s, cs)) std::cout << "true";
    else std::cout << "false";
    return 0;
};