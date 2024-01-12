#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <iostream>

#include "user.hpp"

std::string user_input()
{
  std::string text;
  std::getline(std::cin, text);
  return text;
}

bool login()
{
  int count = 0;
  do {
    std::cout << "Enter username: ";
    std::string username = user_input();
    // TODO: add password masking so user password is not visible on
    // screen
    std::cout << "Enter pincode: ";
    std::string password = user_input();

    User user("John Doe", "0000");
    // TODO: Add login verification
    if (user.verify(username, password)) {
      std::cout << "\nLogin successful.\n"
                << "Welcome " << username << "!\n\n";
      return true;
    }

    ++count;
    std::cout << "Username or pin code is incorrect\n"
              << "Please try again.\n";
  } while (count < 3);
  return false;
}

#endif /* LOGIN_H */
