cmake_minimum_required(VERSION 3.16)

project(YFinancePP)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)

include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)


add_executable(yfdemo demo/yfdemo.cpp
 cpp/base.cpp
 cpp/methods.cpp
 cpp/requests.cpp 
 cpp/utils.cpp
)
target_include_directories(yfdemo PRIVATE hpp cpr::cpr nlohmann_json::nlohmann_json)
target_link_libraries(yfdemo PRIVATE cpr::cpr nlohmann_json::nlohmann_json)