/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** core
*/
#include "../include/plazza.hpp"
using namespace Plazza;

Core::Core(char **av): parser(av)
{
    id = 2;
    msgid = msgget(KEY, 0666 | IPC_CREAT);
    own_msg.id = 1;
}

Core::~Core()
{
    std::cout << "Destroying data" << std::endl;
    msgctl(msgid, IPC_RMID, NULL);
}

void Core::run()
{
    std::cout << "Enter command: ";
    std::string input;
    std::queue<Command> com;
    std::vector<std::string> req;
    std::signal(SIGINT, exit_handler);

    while (std::getline(std::cin, input)) {
        if (parser.is_empty(input)) {
            std::cout << "Enter command: ";
            continue;
        }
        std::cout << "Start sharing " << requests.size() << std::endl;
        std::signal(SIGINT, exit_handler);
        parser.parse(input, com, requests);
        this->share_request();
        std::cout << "Enter command: ";
    }
}

void Core::stop_kitchens()
{
    for (int i = 0; i < kitchens.size(); i++) {
        kill(kitchens[i].pid, SIGINT);
    }
}

void Core::share_request()
{
    std::string str = "";
    std::cout << "Request treating\n";
    while (!requests.empty()) {
        if (kitchens.empty()) {
            Kitchen k(id, parser.cook_nbr);
            kitchens.push_back(k);
        }
        for (int i = 0; i < kitchens.size(); i++) {
            msg.id = i + 2;
            std::string str = requests.front();
            int size = sprintf(msg.msg, "%s", str.c_str());
            msg.msg[size] = '\0';
            msgsnd(msgid, &msg, sizeof(msg), 0);
            std::cout << "Reception send " << msg.msg << " to " << msg.id << std::endl;
            char res[90];
            size = sprintf(res, "%d ok", i + 2);
            res[size] = '\0';
            char err[90];
            size = sprintf(err, "%d ko", i + 2);
            err[size] = '\0';
            msgrcv(msgid, &own_msg, sizeof(message), 1, 0);
            std::cout << "Reception receive [" << own_msg.msg << "] from " << i + 2 << std::endl;
            str = "";
            if (strcmp(own_msg.msg, res) == 0) {
                str = "";
            }
            if (strcmp(own_msg.msg, err) == 0) {
                Kitchen k(i + 3, parser.cook_nbr);
                kitchens.push_back(k);
            }
            if (str == "")
                requests.pop();
        }
    }
    stop_kitchens();
    kitchens.clear();
}
