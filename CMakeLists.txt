cmake_minimum_required(VERSION 3.26)
project(bank)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(bank
        src/account.hpp
        src/bank.hpp
        src/login.hpp
        src/main.cpp
        src/menu.hpp
        src/currency.cpp
        src/currency.hpp
        src/navigation.hpp
        src/transaction.hpp
        src/user.hpp)
