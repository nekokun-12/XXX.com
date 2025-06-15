#include <iostream>
#include "httplib.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main()
{
    httplib::Client cli("localhost", 8080);

    std::cout << " 0 : /help 顯示各種功能 \n";
    while(true)
    {
        int n;
        std::cin >> n;
        if(n == 0)// help
        {


        }
        else if (n == 1)// register
        {
            

            
        }
        else if(n == 2)// user_info/:id
        {


        }
        else if(n == 3)// change_info/:id
        {

        }
        else if(n == 4)// send_Message
        {

        }
        else if(n == 5)// get_message/:index
        {

        }
        else if(n == 6)// end
        {

        }
    }     
    


    return 0;
}