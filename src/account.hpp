#ifndef ACCOUNT_MENU_HPP
#define ACCOUNT_MENU_HPP

#include <iostream>
#include <vector>

#include "transaction.hpp"

class Account
        {
    // TODO
    // Add struct for how accounts look DONE
    // Make it possible to assign them to a user DONE
    // Generate random names and values from a list
private:
    std::string type;
    double balance;
    int id;

public:
    inline static std::vector<Account> accVec;

    Account(std::string type, double balance,int id) {
        type = type;
        balance = balance;
        id = id;
    }


    const std::string &getType() const {
        return type;
    }

    double getBalance() const {
        return balance;
    }

    int getId() const {
        return id;
    }


    bool transfer();
};

#endif //ACCOUNT_MENU_HPP