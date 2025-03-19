/*
** EPITECH PROJECT, 2024
** B-MAT-400-COT-4-1-206neutrinos-hanniel.degbelo
** File description:
** split
*/

#include "../include/split.hpp"


stringsplit::stringsplit(std::string new_str = "")
{
    word = new_str;
    separator = "";
}

stringsplit::stringsplit()
{
    word = "";
    separator = "";
}

stringsplit::~stringsplit()
{
}

void stringsplit::set_separator(std::string sep)
{
    separator = sep;
}

bool stringsplit::check_char(char c)
{
    for (int i = 0; i < separator.length(); i++) {
        if (c == separator.at(i))
            return false;
    }
    return true;
}

std::vector<std::string> stringsplit::split()
{
    std::vector<std::string> result;
    std::string str = "";

    for (int i = 0; i < word.length(); i++) {
        if (this->check_char(word.at(i)) &&
            (i + 1 < word.length() && this->check_char(word.at(i + 1)))) {
            str += word.at(i);
        } else if (this->check_char(word.at(i)) &&
            (i + 1 >= word.length() || !this->check_char(word.at(i + 1)))) {
            str += word.at(i);
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

std::vector<std::string> stringsplit::split(std::string _word, std::string sep)
{
    std::vector<std::string> result;
    std::string str = "";
    word = _word;
    separator = sep;

    // if (word.length() <= 1)
    //     return result;
    for (int i = 0; i < word.length(); i++) {
        if (this->check_char(word.at(i)) &&
            (i + 1 < word.length() && this->check_char(word.at(i + 1)))) {
            str += word.at(i);
        } else if (this->check_char(word.at(i)) &&
            (i + 1 >= word.length() || !this->check_char(word.at(i + 1)))) {
            str += word.at(i);
            result.push_back(str);
            str = "";
        }
    }
    return result;
}
