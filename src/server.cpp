#include <bits/stdc++.h>
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <user/user_info.h>
#include <user/function.h>
#include <user/conversation.h>
using json = nlohmann::json;

// 簡易的用戶結構與資料庫模擬
int main()
{
    httplib::Server svr;
    User info;

    // GET /api/help - 顯示各項功能
    svr.Get("/api/help", [&](const httplib::Request &req, httplib::Response &res) {
        json j;
        j["content"] = functions;
        res.status = 200;
        res.set_content(j.dump(), "application/json");
    });
    
    // POST /api/register - 接收 JSON 格式的新用戶資料，建立新用戶
    svr.Post("/api/register", [&](const httplib::Request &req, httplib::Response &res) {
        try {
            json req_json = json::parse(req.body);
            // 簡單驗證必要欄位是否存在
            for(std::string info : user_info) {
                if (!req_json.contains(info)) {
                    res.status = 400;
                    res.set_content(R"({"error":"Missing some of the info"})", "application/json");
                    return; // 跳出
                }
            }
            // 建立 User 物件並存入資料庫
            User new_user = { next_id, req_json["password"], req_json["name"], req_json["gender"], req_json["age"], req_json["weight"], req_json["height"], req_json["job"], req_json["hobby"] };
            user_db[next_id] = new_user;
            // 準備回傳的 JSON（包含分配的 id）
            json resp;
            resp["id"] = new_user.id;
            resp["password"] = new_user.password;
            resp["name"] = new_user.name;
            resp["gender"] = new_user.gender;
            resp["age"] = new_user.age;
            resp["weight"] = new_user.weight;
            resp["height"] = new_user.height;
            resp["job"] = new_user.job;
            resp["hobby"] = new_user.hobby;
            next_id++;  // 更新下一個可用 ID
            // 設定回應內容與狀態碼 201 (已建立)
            res.status = 201;
            res.set_content(resp.dump(), "application/json");
        }
        catch (json::parse_error& e) {
            // JSON 格式不正確
            res.status = 400;
            res.set_content(R"({"error":"Invalid JSON"})", "application/json");
        }
    });
    
    // GET /api/user_info/:id - 取得指定 ID 的用戶資訊
    svr.Get("/api/user_info/:id", [&](const httplib::Request &req, httplib::Response &res) {
        int user_id = std::stoi(req.path_params.at("id"));  // 取得路徑參數 id 並轉為整數
        if (user_db.find(user_id) == user_db.end()) {
            res.status = 404;
            res.set_content(R"({"error":"User not found"})", "application/json");
            return;
        }

        User u = user_db[user_id];
        json j;
        j["id"] = u.id;
        j["password"] = u.password;
        j["name"] = u.name;
        j["gender"] = u.gender;
        j["age"] = u.age;
        j["weight"] = u.weight;
        j["height"] = u.height;
        j["job"] = u.job;
        j["hobby"] = u.hobby;
        res.status = 200;
        res.set_content(j.dump(), "application/json");
    });

    // POST /api/change_info/:id - 修改指定用戶特定資訊
    svr.Post("/api/users/change_info/:id", [&](const httplib::Request &req, httplib::Response &res) {
        json req_json = json::parse(req.body);
        bool is_valid = false;
        for(int i = 0; i < user_info.size(); i++) {
            if(!req_json.contains(user_info[i]))
            continue;

            
        }

    });

    // POST /api/send - 傳送訊息（加入至conversation中）
    svr.Post("/api/send", [&](const httplib::Request &req, httplib::Response &res) {
        json req_json = json::parse(req.body);
        if(!req_json.contains("message") || !req_json.contains("id")) {
            res.status = 400;
            res.set_content(R"({"error":"Json format error"})", "application/json");
            return;
        }
        if(user_db.find(req_json["id"]) == user_db.end()) {
            res.status = 404;
            res.set_content(R"({"error":"Id not found"})", "application/json");
            return;
        }
        conversation.push_back({ req_json["id"], req_json["message"] });

        res.status = 201;
        res.set_content(R"({"success":"message successfully added to conversation"})", "application/json");
    });

    // Get /api/get_message/:index - 取得指定訊息
    svr.Get("/api/get_message/:index", [&](const httplib::Request &req, httplib::Response &res) {
        int index = std::stoi(req.path_params.at("index"));
        if(0 < index && index <= conversation.size()) {
            json j;
            j["id"] = conversation[index - 1].id;
            j["user"] = user_db[conversation[index - 1].id].name;
            j["content"] = conversation[index - 1].message;
            res.status = 200;
            res.set_content(j.dump(), "application/json");
        }
        else if((0-conversation.size()) <= index && index < 0) {
            json j;
            int s = conversation.size();
            j["id"] = conversation[s - index].id;
            j["user"] = user_db[conversation[s - index].id].name;
            j["content"] = conversation[s - index].message;
            res.status = 200;
            res.set_content(j.dump(), "application/json");
        }
        else {
            res.status = 404;
            res.set_content(R"({"error":"Index out of range"})", "application/json");
        }
    });

    std::cout << "User API 伺服器啟動中..." << std::endl;
    svr.listen("localhost", 8080);
}