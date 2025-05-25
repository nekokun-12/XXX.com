#ifndef USER_INFO_H
#define USER_INFO_H
#include <bits/stdc++.h>

struct User
{
    int id;
    std::string user_name;
    std::string gender;
    int age;
    std::string job;
    int length;
    int weight;
    int height;
    std::string habit;
    std::vector<std::string> conversation_record;
};
static std::map<int, User> user_db = {};
static int next_id = 1;

#endif