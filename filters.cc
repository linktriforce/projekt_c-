#include "filters.h"


bool contains_any_of(const string &s, const string &char_set)
{
    if (char_set.length() == 0)
    {
        return true;
    }

    for (char c : char_set)
    {
        if (s.find(c) != string::npos)
        {
            return true;
        }
    }
    return false;
}

bool contains_at(const string &s, char c, size_type pos)
{
    return s[pos] == c;
}

bool contains_but_not_at(const string &s, char c, size_type pos)
{
    // If c exist in s and it in the wrong pos
    return s.find(c) != string::npos && s.find(c) != pos;
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

bool wrong_fn::operator()(const string &c)
{
    if (l.length() > 0)
    {
        return !contains_any_of(c, l);
    }
    else
    {
        return true;
    }
}

bool correct_fn::operator()(const string &c)
{
    return std::all_of(m.begin(), m.end(), [c](std::pair<size_type, string> p)
                       { return contains_at(c, p.second[0], p.first); });
}

bool misplaced_fn::operator()(const string &c)
{
    // För varje ordpar
    for (wordpair wp : m)
    {
        for (char ch : wp.second)
        {
            // Om någon bokstav returnerar true, sätt till true
            if (!contains_but_not_at(c, ch, wp.first))
            {
                return false;
            }
        }
    }
    return true;
}

bool exclude_word_fn::operator()(const string &word)
{
    return !(w(word) && c(word) && m(word));
}