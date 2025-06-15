#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <string>

std::string functions[6][3] = {
    { "1.help", "/api/help", "顯示各項功能" },
    { "2.register", "/api/register", "接收 JSON 格式的新用戶資料，建立新用戶" },
    { "3.user_info", "/api/user_info/:id", "取得指定 ID 的用戶資訊" },
    { "4.change_info", "/api/change_info/:id", "修改指定用戶特定資訊" },
    { "5.send", "/api/send", "傳送訊息（加入至 conversation 中），索引設為\"id\"與\"message\"" },
    { "6.get_message", "/api/get_message/:index", "取得指定訊息；範圍：1 ~ max、-1 ~ -max" },
    { "0.help", "/api/help", "顯示各項功能" },
    { "1.register", "/api/register", "接收 JSON 格式的新用戶資料，建立新用戶" },
    { "2.user_info", "/api/user_info/:id", "取得指定 ID 的用戶資訊" },
    { "3.change_info", "/api/change_info/:id", "修改指定用戶特定資訊" },
    { "4.send", "/api/send", "傳送訊息（加入至 conversation 中），索引設為\"id\"與\"message\"" },
    { "5.get_message", "/api/get_message/:index", "取得指定訊息；範圍：1 ~ max、-1 ~ -max" },
};

#endif