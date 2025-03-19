/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** cook
*/
#include "../include/plazza.hpp"
using namespace Plazza;

Cook::Cook(std::pair<int,int> ids, std::mutex *mutex, std::condition_variable *selector, KitchenRequest *req): new_thread(&Cook::loop, this, mutex, selector, req)
{
    id = ids.first;
    kitchen_id = ids.second;
}

void Cook::start()
{
    new_thread.join();
}

void Cook::loop(std::mutex *mutex, std::condition_variable *selector, KitchenRequest *req)
{
    std::unique_lock<std::mutex> lock(*mutex);

    while (1) {
        selector->wait(lock);
        if (!req->can_take()) {
            lock.unlock();
            continue;
        }
        std::string st = req->take();
        make_pizza(st);
    }
}

Pizza Cook::make_regina(PizzaSize size)
{
    Pizza pizza(REGINA, size);
    sleep(2);
    return pizza;
}

Pizza Cook::make_margarita(PizzaSize size)
{
    Pizza pizza(MARGARITA, size);
    sleep(1);
    return pizza;
}

Pizza Cook::make_americana(PizzaSize size)
{
    Pizza pizza(AMERICANA, size);
    sleep(2);
    return pizza;
}

Pizza Cook::make_fantasia(PizzaSize size)
{
    Pizza pizza(FANTASIA, size);
    sleep(4);
    return pizza;
}

void Cook::make_pizza(std::string request)
{
    stringsplit str;
    std::vector<std::string> res = str.split(request, " ");
    PizzaSize size;

    if (res[1] == "S")
        size = S;
    if (res[1] == "M")
        size = M;
    if (res[1] == "L")
        size = L;
    if (res[1] == "XL")
        size = XL;
    if (res[1] == "XXL")
        size = XXL;
    if (res[0] == "regina")
        make_regina(size);
    if (res[0] == "margarita")
        make_margarita(size);
    if (res[0] == "americana")
        make_americana(size);
    if (res[0] == "fantasia")
        make_fantasia(size);
}
