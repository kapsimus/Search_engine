cmake_minimum_required(VERSION 3.22)
project(Search_engine)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_executable(Search_engine src/main.cpp include/ConverterJSON.h src/ConverterJSON.cpp include/SearchServer.h
        src/SearchServer.cpp include/InvertedIndex.h src/InvertedIndex.cpp include/ConfigException.h src/ConfigException.cpp include/Stopwatch.h src/Stopwatch.cpp)

target_include_directories(Search_engine PUBLIC include)
target_include_directories(Search_engine PUBLIC ../nlohmann_json/include)
