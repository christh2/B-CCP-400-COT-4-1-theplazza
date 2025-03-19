/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** kitchen
*/
#include "../include/plazza.hpp"
using namespace Plazza;

Kitchen::Kitchen(int _id, int nbr): req(nbr)
{
    pid = -1;
    int size;
    int pd = fork();
    if (pd == 0) {
        msg.id = _id;
        msgid = msgget(KEY, 0666 | IPC_CREAT);
        res.id = 1;
        std::vector<Cook> cooks;
        std::mutex mutex;
        std::condition_variable selector;

        for (int i = 0; i < nbr; i++) {
            cooks.push_back(Cook(std::make_pair(i, _id), &mutex, &selector, &req));
            cooks[i].start();
        }
        while (1) {
            msgrcv(msgid, &msg, sizeof(message), _id, 0);
            std::string str = msg.msg;
            if (str != "status") {
                std::cout << "\t" << "Kitchen " << msg.id << " receives [" << msg.msg << "]" << std::endl;
                // if (req.can_allocate()) {
                //     size = sprintf(res.msg, "%d ok", _id);
                //     mutex.lock();
                //     req.add(str);
                //     mutex.unlock();
                //     selector.notify_one();
                // } else {
                //     size = sprintf(res.msg, "%d ko", _id);
                // }
                // res.msg[size] = '\0';
                // res.id = 1;
                // msgsnd(msgid, &res, sizeof(message), 0);
                // std::cout << "Hanniel\n";
            } else {
                std::cout << "\tKitchen status" << std::endl;
            }
        }
    } else {
        pid = pd;
        std::cout << "Starting kitchen " << _id << std::endl;
    }
}

Kitchen::~Kitchen()
{
}

