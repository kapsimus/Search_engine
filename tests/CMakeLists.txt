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
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
        Search_engine_tests
        my_test.cpp
)
target_link_libraries(
        Search_engine_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Search_engine_tests)