#ifndef USER_INFO_H
#define USER_INFO_H
#include <bits/stdc++.h>

struct User
{
    int id = 0;
    std::string name;
    std::string gender;
    int age = 0;
    std::string job;
    int length = 0;
    int weight = 0;
    int height = 0;
    std::string habit;
    std::vector<std::string> conversation_record;
};
static std::map<int, User> user_db = {};
static int next_id = 1;

#endif