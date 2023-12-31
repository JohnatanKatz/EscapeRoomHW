cmake_minimum_required(VERSION 3.7)
project(MTMex3)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -v -Wall -std=c99 -pedantic-errors -g -Werror -lmtm)

set(SOURCE_FILES main.c EscapeTechnion.c)
set(Test_List ./tests/list_mtm/list_example_test.c list_mtm1.c)

link_directories(libmtm/win64)

add_executable(MTMex3 ${SOURCE_FILES})
add_executable(Test_List_EX ${Test_List})
add_executable(Test Test.c)
add_executable(Binary_search binary_search.c connectedList.c)

target_link_libraries(MTMex3 libmtm.a)
target_link_libraries(Test_List_EX libmtm.a)
target_link_libraries(Test libmtm.a)
target_link_libraries(Binary_search libmtm.a)