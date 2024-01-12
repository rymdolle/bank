#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "account.hpp"

class User
{
public:
  User(std::string name, std::string password)
  {
    name_ = name;
    password_ = password;
  }

  bool verify(std::string name, std::string password)
  {
    return name == name_ && password_ == password;
  }

private:
  std::vector<Account> acounts_;
  std::string name_;
  std::string password_;
};

#endif /* USER_H */
