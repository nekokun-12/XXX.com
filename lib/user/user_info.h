#ifndef USER_INFO_H
#define USER_INFO_H
#include <bits/stdc++.h>
using namespace std;

struct User
{
    int id;
    string name;
    string gender;
    int age;
    string job;
    int length;
    int weight;
    int height;
    string habit;
    vector<string> conversation_record;
};
static map<int, User> user_db = {};
static int next_id = 1;

#endif