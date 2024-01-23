#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "account.hpp"

class User {

private:
    std::string name_;
    std::string password_;
    int id_;
public:

    User(std::string name, std::string password, int id) {
        name_ = name;
        password_ = password;
        id_ = id;
    }

  User() {}

    std::string toString() const {
        return "Name: " + name_ + "\nPin: " + getPassword() + "\nID: " + std::to_string(id_) + "\n";
    }

    bool verify(std::string& name, std::string& password) const {
        return name == name_ && password_ == password;
    }

    // Getters

    const std::string& getName() const {
        return name_;
    }

    const std::string& getPassword() const {
        return password_;
    }

    int getId() const {
        return id_;
    }

    static std::vector<User> loadFromFile(std::string filename)
    {
        std::ifstream file(filename);
        std::vector<User> users;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string username, password;
            std::getline(ss, username, ':');
            std::getline(ss, password, ':');
            int id;
            ss >> id;
            users.emplace_back(username, password, id);
        }
        return users;
  }

  std::vector<Account> getAccounts()
  {
    std::vector<Account> accounts;
    for (Account& a : Account::getAccounts()) {
      if (a.getId() == id_)
        accounts.push_back(a);
    }
    return accounts;
  }
};


#endif /* USER_H */
