#ifndef ACCOUNT_MENU_HPP
#define ACCOUNT_MENU_HPP

#include <iostream>
#include <string>
#include <vector>

#include "transaction.hpp"

class Account
        {
    // TODO: Generate random account names and values from an array
private:
    std::string type_;
    int64_t balance_;
    int id_;

public:
    std::string currency;

    Account(std::string type, int64_t balance,int id) {
        type_ = type;
        balance_ = balance;
        id_ = id;
        currency = "SEK";
    }


    const std::string &getType() const {
        return type_;
    }

    int64_t& getBalance() {
        return balance_;
    }

    int getId() const {
        return id_;
    }


    bool transfer();
};

#endif //ACCOUNT_MENU_HPP
