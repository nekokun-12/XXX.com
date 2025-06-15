#ifndef FUNCTION_H
#define FUNCTION_H
#include <bits/stdc++.h>

std::string functions[6][3] = {
    { "/api/help", "顯示各項功能" }, // URL, type, intro
    { "/api/register", "接收 JSON 格式的新用戶資料，建立新用戶" },
    { "/api/user_info/:id", "取得指定 ID 的用戶資訊" },
    { "/api/change_info/:id", "修改指定用戶特定資訊" },
    { "/api/send", "傳送訊息（加入至 conversation 中），索引設為\"id\"與\"message\"" },
    { "/api/get_message/:index", "取得指定訊息；範圍：1 ~ max、-1 ~ -max" },
};

#endif