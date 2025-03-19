/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** pizza
*/
#include "../include/plazza.hpp"
using namespace Plazza;

Pizza::Pizza()
{
}

Pizza::Pizza(PizzaType _type, PizzaSize _size)
{
    size = _size;
    type = _type;
}
