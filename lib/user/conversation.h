#ifndef CONVERSATION_H
#define CONVERSATION_H
#include <bits/stdc++.h>

struct Message
{
    int id = 0;
    std::string message;
};

static std::vector<Message> conversation = {};

#endif