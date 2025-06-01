#ifndef FUNCTION_H
#define FUNCTION_H
#include <bits/stdc++.h>

std::string functions[6][3] = {
    { "/api/help", "GET", "顯示各項功能" }, // URL, type, intro
    { "/api/register", "POST", "接收 JSON 格式的新用戶資料，建立新用戶" },
    { "/api/user_info/:id", "GET", "取得指定 ID 的用戶資訊" },
    { "/api/change_info/:id/:info", "POST", "修改指定用戶特定資訊" },
    { "/api/send/:id", "POST", "傳送訊息（加入至 conversation 中）" },
    { "/api/get_message/:index", "GET", "取得指定訊息；範圍：1 ~ max、-1 ~ -max" },
};

#endif