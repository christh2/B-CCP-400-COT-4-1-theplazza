/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** main
*/
#include "../include/plazza.hpp"
using namespace Plazza;
Core *core;

void Plazza::exit_handler(int sig)
{
    core->stop_kitchens();
    //delete core;
    std::exit(0);
}

int main(int ac, char **av)
{
    Core ar(av);
    core = &ar;
    core->run();
}
