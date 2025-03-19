/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** plazza
*/
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <unistd.h>
#include <sys/types.h>
#include "split.hpp"
#include <sys/wait.h>
#include <csignal>
#include <cstring>
#include <cstdlib>
#pragma once
#define KEY 12
#define SIZE 120

namespace Plazza {
    typedef struct message message;
    struct message {
        long id;
        char msg[SIZE];
    };
    enum PizzaType {
        REGINA = 1,
        MARGARITA = 2,
        AMERICANA = 4,
        FANTASIA = 8
    };
    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    class Command {
        public:
            Command(PizzaSize _size, PizzaType _type, int _nbr);
            PizzaSize size;
            PizzaType type;
            int nbr;
    };
    class Pizza {
        public:
            Pizza(PizzaType _type, PizzaSize _size);
            Pizza();
            PizzaSize size;
            PizzaType type;
    };
    class KitchenRequest {
        public:
            KitchenRequest(int nbr);
            bool can_allocate();
            void add(std::string req);
            bool can_take();
            std::string take();
        private:
            int max;
            std::queue<std::string> request;
    };
    class Cook {
        public:
            Cook(std::pair<int, int> ids, std::mutex *mutex, std::condition_variable *selector, KitchenRequest *req);
            void start();
            void loop(std::mutex *mutex, std::condition_variable *selector, KitchenRequest *req);
            std::thread new_thread;
        private:
            void make_pizza(std::string request);
            Pizza make_regina(PizzaSize size);
            Pizza make_margarita(PizzaSize size);
            Pizza make_americana(PizzaSize size);
            Pizza make_fantasia(PizzaSize size);
            int id;
            int kitchen_id;
    };
    class Kitchen {
        public:
            Kitchen(int _id, int nbr);
            ~Kitchen();
            int pid;
            message msg;
            message res;
        private:
            KitchenRequest req;
            int msgid;
    };
    class Parser {
        public:
            Parser(char **av);
            bool is_empty(std::string word);
            void parse(std::string _command, std::queue<Command> &com, std::queue<std::string> &r);
            int speed;
            int cook_nbr;
            int regeneration_time;
        private:
            Command make_command(std::string com);
            std::pair<bool, std::string> get_pizza_nbr(std::string com);
            bool format_request(std::string command, std::queue<std::string> &req, std::queue<Command> &com);
    };
    class Core {
        public:
            Core(char **av);
            ~Core();
            void run();
            void stop_kitchens();
        private:
            Parser parser;
            int id;
            std::vector<Kitchen> kitchens;
            int msgid;
            message msg;
            message own_msg;
            std::queue<std::string> requests;

            void share_request();
    };
    void exit_handler(int sig);
}
