#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <vector>

#include "user.hpp"
#include "account.hpp"

std::string user_input()
{
  std::string text;
  std::getline(std::cin, text);
  return text;
}

bool login(User &currentUser, std::vector<User> *userVec)
{
  int count = 0;
  do {
    std::cout << "Enter username:";
    std::string username = user_input();
    // TODO: add password masking so user password is not visible on
    // screen
    std::cout << "Enter pin code:";
    std::string password = user_input();


    // Runs through the list of users and calls the verify method to check if it is a valid login
      for (const auto &user : *userVec) {
          if (user.verify(username, password)) {
              std::cout << "\nLogin successful.\n"
                        << "Welcome " << username << "!\n\n";
              // Assigns the user object currentUser the valid user object
              currentUser = user;
              return true;
          }
      }

      // TODO: Add login verification

    ++count;
    std::cout << "\nUsername or pin code is incorrect\n"
              << "Please try again.\n";
  } while (count < 3);
  return false;
}

#endif /* LOGIN_H */
