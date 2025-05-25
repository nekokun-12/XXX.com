#ifndef USER_INFO_H
#define USER_INFO_H

struct User
{
    int id;
    std::string name;
    int age;
    std::vector<std::string> conversation_record;
};
static std::map<int, User> user_db = {};
static int next_id = 1;

#endif