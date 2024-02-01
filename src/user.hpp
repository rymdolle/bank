//user.hpp
#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "account.hpp"
#include "database.hpp"

#include <sql.h>
#include <sqltypes.h>

class User {

private:
    std::string name_;
    std::string password_;
    int id_;
    std::vector<Account> accounts_;
public:

  User(std::string name, std::string password, int id) {
    name_ = name;
    password_ = password;
    id_ = id;
    for (Account& a : Account::getAccounts()) {
      if (a.getUserId() == id_)
        accounts_.push_back(a);
    }
  }

  User() {}

    std::string toString() const {
        return "Name: " + name_ + "\nPin: " + getPassword() + "\nID: " + std::to_string(id_) + "\n";
    }

    bool verify(std::string& name, std::string& password) const {
        return name == name_ && password_ == password;
    }

  static std::vector<User> loadFromDatabase(std::string username)
  {
    std::vector<User> users;
    Database& db = Database::getInstance();
    std::stringstream query;
    query << "SELECT id, password "
          << "FROM bank.users "
          << "WHERE username = '" << username << "'";
    SQLHSTMT hstmt = db.execQuery(query.str());
    if (!hstmt)
      return users;
    SQLRETURN ret = SQLFetch(hstmt);
    if (SQL_SUCCEEDED(ret)) {
      int id = Database::read_integer(hstmt, 1);
      std::string password = Database::read_string(hstmt, 2);
      users.emplace_back(username, password, id);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return users;
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
    //load from file users
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

  std::vector<Account>& getAccounts()
  {
    return accounts_;
  }

  void createAccount(Account newAccount)
  {
    accounts_.push_back(newAccount);
  }

};


#endif /* USER_H */
