/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** kitchen_request
*/
#include "../include/plazza.hpp"
using namespace Plazza;

KitchenRequest::KitchenRequest(int nbr)
{
    max = 2 * nbr;
}

bool KitchenRequest::can_allocate()
{
    return (request.size() < max);
}

void KitchenRequest::add(std::string req)
{
    if (!can_allocate())
        return;
    request.push(req);
}

bool KitchenRequest::can_take()
{
    return (request.size() > 0);
}

std::string KitchenRequest::take()
{
    std::string req = request.front();
    request.pop();
    return req;
}
