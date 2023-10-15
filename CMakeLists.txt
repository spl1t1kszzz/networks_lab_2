cmake_minimum_required(VERSION 3.26)
project(networks_lab_2_cpp_main_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(networks_lab_2_cpp_main_2
        main.cpp
        client/tcp_client.cpp
        client/tcp_client.hpp
        server/tcp_handler.cpp
        server/tcp_handler.hpp
        server/tcp_server.cpp
        server/tcp_server.hpp
        timer/timer.hpp
        timer/timer.cpp)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(networks_lab_2_cpp_main_2 ${Boost_LIBRARIES})
