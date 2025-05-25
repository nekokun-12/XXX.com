#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "httplib.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// 簡易的用戶結構與資料庫模擬
struct User
{
    int id;
    std::string name;
    int age;
    std::vector<std::string> conversation_record;
};
static std::map<int, User> user_db = {};
static int next_id = 1;

int main()
{
    httplib::Server svr;

    // GET /api/users/:id - 取得指定 ID 的用戶資訊
    svr.Get("/api/users/:id", [&](const httplib::Request &req, httplib::Response &res) {
        int user_id = std::stoi(req.path_params.at("id"));  // 取得路徑參數 id 並轉為整數
        if (user_db.find(user_id) != user_db.end()) {
            // 找到用戶，構造 JSON 回應
            User u = user_db[user_id];
            json j;
            j["id"] = u.id;
            j["name"] = u.name;
            j["age"] = u.age;
            res.set_content(j.dump(), "application/json");
        } else {
            // 找不到用戶，回傳 404
            res.status = 404;
            json err;
            err["error"] = "User not found";
            res.set_content(err.dump(), "application/json");
        } });

    // POST /api/users - 接收 JSON 格式的新用戶資料，建立新用戶
    svr.Post("/api/users", [&](const httplib::Request &req, httplib::Response &res)
             {
            try {
                json req_json = json::parse(req.body);
                // 簡單驗證必要欄位是否存在
                if (!req_json.contains("name") || !req_json.contains("age")) {
                    res.status = 400;
                    res.set_content(R"({"error":"Missing name or age"})", "application/json");
                    return;
                }
                // 取得新用戶資料
                std::string name = req_json["name"];
                int age = req_json["age"];
                // 建立 User 物件並存入資料庫
                User new_user = { next_id, name, age };
                user_db[next_id] = new_user;
                // 準備回傳的 JSON（包含分配的 id）
                json resp;
                resp["id"] = new_user.id;
                resp["name"] = new_user.name;
                resp["age"] = new_user.age;
                next_id++;  // 更新下一個可用 ID
                // 設定回應內容與狀態碼 201 (已建立)
                res.status = 201;
                res.set_content(resp.dump(), "application/json");
            } catch (json::parse_error& e) {
                // JSON 格式不正確
                res.status = 400;
                res.set_content(R"({"error":"Invalid JSON"})", "application/json");
            } });

    std::cout << "User API 伺服器啟動中..." << std::endl;
    svr.listen("localhost", 8080);
}