#ifndef CONVERSATION_H
#define CONVERSATION_H
#include <iostream>
#include <vector>
#include <string>

struct Message
{
    int id = 0;
    std::string message;
};

static std::vector<Message> conversation = {};

#endif