#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <string>
#include <vector>
#include <iostream>

#include "menu.hpp"
#include "user.hpp"
#include "transaction.hpp" // Flytta denna hit

class Navigation
{
private:
    Menu main_menu;
    User &currentUser;

    enum MenuID
    {
        MAIN,
        ACCOUNT,
        TRANSFER,
        EXCHANGE,
    };

public:
    Navigation(User &loggedUser);

    //void showUserAccounts(const std::vector<Account> &accounts);

    void run();
};

#endif /* NAVIGATION_H */
