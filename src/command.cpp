/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** command
*/
#include "../include/plazza.hpp"
using namespace Plazza;

Command::Command(PizzaSize _size, PizzaType _type, int _nbr)
{
    size = _size;
    type = _type;
    nbr = _nbr;
}
