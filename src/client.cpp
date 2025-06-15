#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <user/user_info.h>
#include <user/function.h>
#include <user/conversation.h>
using json = nlohmann::json;

int main()
{
    httplib::Client cli("localhost", 8080);

    std::cout << " 輸入0 : /help 顯示各種功能 \n";
    while(true)
    {
        int n,id = 1;
        std::cin >> n;
        if(n == 0)// help
        {
            // POST /api/help - 顯示各項功能
            if (auto res = cli.Post("/api/help")){
                if (res -> status == 200){
                    json user_json = json::parse(res->body);
                    std::cout << "Please enter the number." << std::endl;
                    for (int i = 0; i != 6; i++){
                        std::cout << user_json[i][0] << " : " << user_json[i][2];
                    }
                }
                else if (res -> status == 404){

                }
            else {
                std::cout << "POST 請求失敗\n";
            }}


        }
        
        else if (n == 1)// register
        {
            std::cout << "\n建立新用戶（輸入資料）" << std::endl;

            std::string password, name,gender,  job, hobby;
            int age, weight, height;
            
            std::cout << "請輸入帳號密碼：";
            std::getline(std::cin, password);
            std::cout << "請輸入姓名：";
            std::getline(std::cin, name);
            std::cout << "請輸入性別：";
            std::getline(std::cin, gender);
            std::cout << "請輸入年齡：";
            std::cin >> age;
            std::cout << "請輸入體重：";
            std::cin >> weight;
            std::cout << "請輸入身高：";
            std::cin >> height;
            std::cin.ignore(); // 清除 cin 的換行殘留
            std::cout << "請輸入職業：";
            std::getline(std::cin, job);
            std::cout << "請輸入興趣：";
            std::getline(std::cin, hobby);

            // 組成 JSON
            json new_user = {
                {"password", password},
                {"name", name},
                {"gender", gender},
                {"age", age},
                {"weight", weight},
                {"height", height},
                {"job", job},
                {"hobby", hobby}
            };

            // 發送 POST 請求
            auto res2 = cli.Post("/api/register", new_user.dump(), "application/json");
            int new_id = -1;
            if (res2 && res2->status == 201) {
                std::cout << "用戶建立成功：" << res2->body << std::endl;
                auto resp_json = json::parse(res2->body);
                new_id = resp_json["id"];
            } else {
                std::cerr << "建立用戶失敗，狀態：" << (res2 ? res2->status : 0) << std::endl;
                return 1;
            }
            std::cout << "Your id is: " << id << "\n" ;
            id++;
            
        }
        else if(n == 2)// user_info/:id
        {
            httplib::Client cli("localhost", 8080); // 本機伺服器


            int id;
            std::cout << "請輸入要查詢的用戶 ID：";
            std::cin >> id;


            // 建立 JSON 請求資料
            json request_body = {
                {"id", id}
            };


            // 傳送 POST 請求，內容為 JSON
            auto res = cli.Post("/api/get_user", request_body.dump(), "application/json");


            if (res && res->status == 200) {
                // 成功收到伺服器回應
                json user = json::parse(res->body);
                std::cout << "查詢成功：" << std::endl;
                std::cout << "ID: " << user["id"] << std::endl;
                std::cout << "姓名: " << user["name"] << std::endl;
                std::cout << "年齡: " << user["age"] << std::endl;
                std::cout << "性別: " << user["gender"] << std::endl;
                std::cout << "體重: " << user["weight"] << std::endl;
                std::cout << "身高: " << user["height"] << std::endl;
                std::cout << "職業: " << user["job"] << std::endl;
                std::cout << "興趣: " << user["hobby"] << std::endl;
            } else if (res && res->status == 404) {
                std::cout << "用戶不存在。" << std::endl;
            } else {
                std::cout << "查詢失敗，狀態碼：" << (res ? res->status : 0) << std::endl;
                if (res) {
                    std::cout << "回應內容：" << res->body << std::endl;
                }
            }


        }

        else if(n == 3)// change_info/:id
        {
            httplib::Client cli("localhost", 8080);

            int id;
            std::cout << "請輸入要修改的用戶 ID：";
            std::cin >> id;
            std::cin.ignore(); // 清除換行符號

            std::string name, gender, job, hobby;
            int age;
            double weight, height;

            std::cout << "請輸入新的姓名 (留空不修改)：";
            std::getline(std::cin, name);
            std::cout << "請輸入新的年齡 (留空不修改)：";
            std::string age_str;
            std::getline(std::cin, age_str);
            std::cout << "請輸入新的性別 (留空不修改)：";
            std::getline(std::cin, gender);
            std::cout << "請輸入新的體重 (留空不修改)：";
            std::string weight_str;
            std::getline(std::cin, weight_str);
            std::cout << "請輸入新的身高 (留空不修改)：";
            std::string height_str;
            std::getline(std::cin, height_str);
            std::cout << "請輸入新的職業 (留空不修改)：";
            std::getline(std::cin, job);
            std::cout << "請輸入新的興趣 (留空不修改)：";
            std::getline(std::cin, hobby);

            // 建立 JSON，只有非空欄位會被加入
            json update_body;
            update_body["id"] = id;
            if (!name.empty()) update_body["name"] = name;
            if (!age_str.empty()) update_body["age"] = std::stoi(age_str);
            if (!gender.empty()) update_body["gender"] = gender;
            if (!weight_str.empty()) update_body["weight"] = std::stod(weight_str);
            if (!height_str.empty()) update_body["height"] = std::stod(height_str);
            if (!job.empty()) update_body["job"] = job;
            if (!hobby.empty()) update_body["hobby"] = hobby;

            auto res = cli.Post("/api/update_user", update_body.dump(), "application/json");

            if (res && res->status == 200) {
                std::cout << "用戶資訊修改成功！" << std::endl;
                json updated_user = json::parse(res->body);
                std::cout << "最新資料：" << updated_user.dump(4) << std::endl;
            } else {
                std::cout << "修改失敗，狀態碼：" << (res ? res->status : 0) << std::endl;
                if (res) {
                    std::cout << "回應內容：" << res->body << std::endl;
                }
            }
        }
        else if(n == 4)// send_Message
        {
            int id;
            std::string message;
            std::cin.ignore(); // 清除換行殘留
            std::cout << "\n請輸入用戶 ID：";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "請輸入訊息內容：";
            std::getline(std::cin, message);

            json msg = {
                {"id", id},
                {"message", message}
            };

            auto res = cli.Post("/api/send", msg.dump(), "application/json");
            if (res && res->status == 201) {
                std::cout << "訊息傳送成功：" << res->body << std::endl;
            } else {
                std::cerr << "傳送失敗，狀態：" << (res ? res->status : 0) << std::endl;
            }
        }
        else if(n == 5)// get_message/:index
        {

        }
        else if(n == 6)// end
        {
            break;
        }
    }     
 


    return 0;
}