cmake_minimum_required(VERSION 3.26)
project(bank)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts PrintSupport)

include_directories(src)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(bank
        src/account.hpp
        src/account.cpp
        src/bank.hpp
        src/login.hpp
        src/main.cpp
        src/menu.hpp
        src/main_menu.hpp
        src/exchange_menu.hpp
        src/transfer_menu.hpp
        src/account_menu.hpp
        src/currency.cpp
        src/currency.hpp
        src/transaction.hpp
        src/transaction.cpp
        src/user.hpp)

add_executable(bank_gui
        src/main_gui.cpp
        src/mainwindow.cpp
        src/mainwindow.hpp
        src/dashboardwindow.cpp
        src/dashboardwindow.hpp
        src/transferwindow.cpp
        src/transferwindow.hpp
        src/historywindow.cpp
        src/historywindow.hpp
        src/registerwindow.cpp
        src/registerwindow.hpp
        src/createaccountwindow.cpp
        src/createaccountwindow.hpp
        src/changepasswordwindow.cpp
        src/changepasswordwindow.hpp
        src/depositwindow.cpp
        src/depositwindow.hpp
        src/interestwindow.cpp
        src/interestwindow.hpp
        src/withdrawwindow.cpp
        src/withdrawwindow.hpp
        src/profilewindow.cpp
        src/profilewindow.hpp
        src/loanwindow.cpp
        src/loanwindow.hpp
        src/chartwindow.cpp
        src/chartwindow.hpp
        src/notificationwindow.cpp
        src/notificationwindow.hpp
        src/recurringtransferwindow.cpp
        src/recurringtransferwindow.hpp
        src/budgetwindow.cpp
        src/budgetwindow.hpp
        src/supportwindow.cpp
        src/supportwindow.hpp
        src/settingswindow.cpp
        src/settingswindow.hpp
        src/backupwindow.cpp
        src/backupwindow.hpp
        src/restorewindow.cpp
        src/restorewindow.hpp
        src/twofactorwindow.cpp
        src/twofactorwindow.hpp
        src/helpwindow.cpp
        src/helpwindow.hpp
        src/forgotpasswordwindow.cpp
        src/forgotpasswordwindow.hpp
        src/account.hpp
        src/account.cpp
        src/bank.hpp
        src/login.hpp
        src/currency.cpp
        src/currency.hpp
        src/transaction.hpp
        src/transaction.cpp
        src/user.hpp)

target_link_libraries(bank_gui PRIVATE Qt6::Widgets Qt6::Charts Qt6::PrintSupport)
