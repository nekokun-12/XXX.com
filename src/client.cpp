#include <iostream>
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <user/user_info.h>
#include <user/function.h>
#include <user/conversation.h>
using json = nlohmann::json;

int main()
{
    httplib::Client cli("localhost", 8080);


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
        std::cout << "GET 請求失敗\n";
    }
    }


    std::cout << " 0 : /help 顯示各種功能 \n";
    while(true)
    {
        int n,id = 1;
        std::cin >> n;
        if(n == 0)// help
        {


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


        }
        else if(n == 3)// change_info/:id
        {

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