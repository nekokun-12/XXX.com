#ifndef USER_INFO_H
#define USER_INFO_H
#include <bits/stdc++.h>

struct User
{
    int id = 0;
    int password = 0;
    std::string name;
    std::string gender;
    int age = 0;
    int weight = 0;
    int height = 0;
    std::string job;
    std::vector<std::string> habit;
};
std::vector<std::string> user_info = {"password", "name", "gender", "age", "weight", "height", "job", "habit"};
static std::map<int, User> user_db = {};
static std::map<int, std::string> conversation = {};
static int next_id = 1;

#endif