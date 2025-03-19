/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** test
*/
#include "include/plazza.hpp"
using namespace Plazza;

int main(int ac, char **av)
{
    message msg;
    message own;
    own.id = 0;
    msg.id = 1;

    int id = msgget(KEY, 0666 | IPC_CREAT);

    while (1) {
        std::size_t size = msgrcv(id, &msg, sizeof(message), msg.id, 0);
        if (size <= 0) {
            std::cout << "wait\n";
            continue;
        }
        std::cout << "Read " << size << " data: " << msg.msg << std::endl;
        size = sprintf(own.msg, "OK");
        own.msg[size] = '\0';
        msgsnd(id, &own, sizeof(message), 0);
    }
}