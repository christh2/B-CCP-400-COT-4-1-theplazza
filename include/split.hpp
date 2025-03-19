/*
** EPITECH PROJECT, 2024
** The plazza
** File description:
** split
*/

#pragma once
#include <iostream>
#include <vector>

class stringsplit {
    public:
        stringsplit(std::string new_str);
        stringsplit();
        ~stringsplit();
        void set_separator(std::string sep);
        std::vector<std::string> split();
        std::vector<std::string> split(std::string _word, std::string sep);
    private:
        bool check_char(char c);
        std::string word;
        std::string separator;
};
