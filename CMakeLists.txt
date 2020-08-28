
cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

add_executable(test ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

#target_include_directories(test PRIVATE ${bullet_manager_include_dirs})

target_link_libraries(test sfml-graphics bullet_manager)

