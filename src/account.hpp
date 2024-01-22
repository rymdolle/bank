#ifndef ACCOUNT_MENU_HPP
#define ACCOUNT_MENU_HPP

#include <fstream>
#include <iostream>
#include <sstream>
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

    static std::vector<Account> accounts_;

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

    static std::vector<Account>& getAccounts()
    {
      return accounts_;
    }

  static std::vector<Account> loadFromFile(std::string filename)
  {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip first line
    while (std::getline(file, line)) {
      if (line.empty())
        continue;
      std::stringstream ss(line);
      std::string name, currency;
      int64_t id, balance;
      std::getline(ss, name, '\t');
      ss >> id;
      ss >> balance;
      std::getline(ss, currency);
      accounts_.emplace_back(name, balance, id);
    }
    return accounts_;
  }
};

#endif //ACCOUNT_MENU_HPP
