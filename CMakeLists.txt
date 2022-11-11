cmake_minimum_required(VERSION 3.22)
project(Search_engine)

set(CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(Search_engine main.cpp include/ConverterJSON.h src/ConverterJSON.cpp include/SearchServer.h src/SearchServer.cpp include/InvertedIndex.h src/InvertedIndex.cpp)
target_include_directories(Search_engine PUBLIC include)

target_link_libraries(Search_engine PRIVATE nlohmann_json::nlohmann_json)
