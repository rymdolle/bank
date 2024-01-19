#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <vector>
#include <filesystem>

#include "user.hpp"
#include "account.hpp"

std::string user_input()
{
  std::string text;
  std::getline(std::cin, text);
  return text;
}

bool login(User &currentUser)
{
  int count = 0;
  do {
    std::cout << "Enter username:";
    std::string username = user_input();
    // TODO: add password masking so user password is not visible on
    // screen
    std::cout << "Enter pin code:";
    std::string password = user_input();

    for (User &user : User::loadFromFile("data/users.txt")) {
      if (user.verify(username, password)) {
        std::cout << "\nLogin successful.\n"
                  << "Welcome " << username << "!\n\n";
        currentUser = user;
        return true;
      }
    }

    ++count;
    std::cout << "\nUsername or pin code is incorrect\n"
              << "Please try again.\n";
  } while (count < 3);
  return false;
}

#endif /* LOGIN_H */
