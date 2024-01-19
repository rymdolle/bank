cmake_minimum_required(VERSION 3.26)
project(bank)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(bank
        src/account.hpp
        src/bank.hpp
        src/login.hpp
        src/main.cpp
        src/menu.hpp
        src/navigation.hpp
        src/transaction.hpp
        src/user.hpp)
