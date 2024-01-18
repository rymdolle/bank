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
    std::string type_;
    double balance_;
    int id_;

public:

    Account(std::string type, double balance,int id) {
        type_ = type;
        balance_ = balance;
        id_ = id;
    }


    const std::string &getType() const {
        return type_;
    }

    double getBalance() const {
        return balance_;
    }

    int getId() const {
        return id_;
    }


    bool transfer();
};

#endif //ACCOUNT_MENU_HPP