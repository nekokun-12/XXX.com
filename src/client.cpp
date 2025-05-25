#include <iostream>
#include "httplib.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main()
{
    httplib::Client cli("localhost", 8080);

    // 呼叫 GET /api/users/1，嘗試取得 ID 為 1 的用戶資料
    if (auto res = cli.Get("/api/users/1"))
    {
        if (res->status == 200)
        {
            json user_json = json::parse(res->body);
            std::cout << "用戶1 姓名：" << user_json["name"]
                      << "，年齡：" << user_json["age"] << std::endl;
        }
        else if (res->status == 404)
        {
            std::cout << "用戶1 不存在！" << std::endl;
        }
    }
    else
    {
        std::cout << "GET 請求失敗\n";
    }

    // 準備新用戶的資料 JSON 並呼叫 POST /api/users 建立用戶
    json new_user;
    new_user["name"] = "小明";
    new_user["age"] = 20;
    auto res2 = cli.Post("/api/users", new_user.dump(), "application/json");
    if (res2 && res2->status == 201)
    {
        json created = json::parse(res2->body);
        std::cout << "成功建立用戶：ID=" << created["id"]
                  << "，姓名=" << created["name"]
                  << "，年齡=" << created["age"] << std::endl;
    }
    else
    {
        std::cout << "建立用戶失敗，狀態碼：" << (res2 ? res2->status : 0) << std::endl;
    }

    // 再次呼叫 GET /api/users/1 取得剛建立的用戶
    if (auto res3 = cli.Get("/api/users/1"))
    {
        if (res3->status == 200)
        {
            json user_json = json::parse(res3->body);
            std::cout << "用戶1 最新資訊：姓名=" << user_json["name"]
                      << "，年齡=" << user_json["age"] << std::endl;
        }
    }

    return 0;
}