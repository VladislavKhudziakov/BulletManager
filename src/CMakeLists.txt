
file(GLOB_RECURSE SRC internal/*.cpp)

add_library(bullet_manager STATIC ${SRC})

target_include_directories(bullet_manager PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(bullet_manager PRIVATE sfml-graphics)