include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY
        https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(TestCaseInvertedIndex my_test.cpp ../modules/include/ConverterJSON.h ../modules/src/ConverterJSON.cpp ../modules/include/SearchServer.h
        ../modules/src/SearchServer.cpp ../modules/include/InvertedIndex.h ../modules/src/InvertedIndex.cpp)

target_include_directories(TestCaseInvertedIndex PUBLIC ../modules/include)
target_include_directories(TestCaseInvertedIndex PUBLIC ../nlohmann_json/include)

target_link_libraries(
        TestCaseInvertedIndex
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestCaseInvertedIndex)