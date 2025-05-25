cmake_minimum_required(VERSION 3.10) 
project(cpp_http)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)


FetchContent_Declare(
  httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG v0.15.3
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(httplib)


FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nlohmann_json)


add_executable(server src/server.cpp) 
add_executable(client src/client.cpp) 

target_link_libraries(server PRIVATE httplib::httplib nlohmann_json::nlohmann_json)
target_link_libraries(client PRIVATE httplib::httplib nlohmann_json::nlohmann_json)