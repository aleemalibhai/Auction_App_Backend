cmake_minimum_required(VERSION 3.15)
project(Auction_App)

set(CMAKE_CXX_STANDARD 14)

add_executable(Auction_App user.cpp item.cpp data.cpp driver.cpp main.cpp)
