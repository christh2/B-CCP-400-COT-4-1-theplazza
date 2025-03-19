/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** parser
*/
#include "../include/plazza.hpp"
using namespace Plazza;

Parser::Parser(char **av)
{
    speed = std::stoi(av[1]);
    cook_nbr = std::stoi(av[2]);
    regeneration_time = std::stoi(av[3]);
}

bool Parser::is_empty(std::string word)
{
    stringsplit str(word);
    str.set_separator(" \n\t");
    std::vector vect = str.split();

    return vect.empty();
}

void Parser::parse(std::string _command, std::queue<Command> &com, std::queue<std::string> &r)
{
    stringsplit str;
    std::queue<std::string> req;
    std::vector<std::string> com_res = str.split(_command, ";\n");

    for (int i = 0; i < com_res.size(); i++) {
        if (!format_request(com_res[i], r, com)) {
            break;
        }
    }
}

/* private */
Command Parser::make_command(std::string com)
{
    stringsplit str(com);
    std::vector<std::string> res = str.split(com, " ");
    PizzaSize size;
    PizzaType type;
    int nbr = std::stoi(get_pizza_nbr(res[2]).second);

    if (res[0] == "regina")
        type = REGINA;
    else if (res[0] == "margarita")
        type = MARGARITA;
    else if (res[0] == "americana")
        type = AMERICANA;
    else
        type = FANTASIA;
    
    if (res[1] == "S")
        size = S;
    else if (res[1] == "M")
        size = M;
    else if (res[1] == "L")
        size = L;
    else if (res[1] == "XL")
        size = XL;
    else
        size = XXL;
    Command command(size, type, nbr);
    return command;
}

std::pair<bool, std::string> Parser::get_pizza_nbr(std::string com)
{
    if (com[0] != 'x')
        return std::make_pair(false, "");
    stringsplit str(com);
    std::vector res = str.split(com, "x");
    if (res.empty()) {
        return std::make_pair(false, "");
    }
    if (res.size() != 1)
        std::make_pair(false, "");
    for (int i = 0; i < res[0].length(); i++) {
        if (res[0][i] < '0' || res[0][i] > '9')
            return std::make_pair(false, "");
    }
    return std::make_pair(true, res[0]);
}

bool Parser::format_request(std::string command, std::queue<std::string> &req, std::queue<Command> &com)
{
    stringsplit str(command);
    std::vector<std::string> result = str.split(command, " ");
    if (result.size() != 3) {
        std::cerr << "Invalid command arguments size" << std::endl;
        return false;
    }
    if (result[0] != "regina" && result[0] != "margarita" && result[0] != "americana"
    && result[0] != "fantasia") {
        std::cerr << "Invalid pizza type" << std::endl;
        return false;
    }
    if (result[1] != "S" && result[1] != "M" && result[1] != "L" && result[1] != "XL"
    && result[1] != "XXL") {
        std::cerr << "Invalid pizza size" << std::endl;
        return false;
    }
    std::pair<bool, std::string> truth = get_pizza_nbr(result[2]);
    if (truth.first == false) {
        std::cerr << "Invalid pizza number" << std::endl;
        return false;
    }
    int nbr = std::stoi(truth.second);
    for (int i = 0; i < nbr; i++) {
        std::string to_push = result[0] + " " + result[1];
        req.push(to_push);
    }
    // std::cout << "Error" << std::endl;
    // com.push(make_command(command));
    return true;
}
