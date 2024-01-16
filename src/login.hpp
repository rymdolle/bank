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
    std::cout << "Enter username:";
    std::string username = user_input();
    // TODO: add password masking so user1 password is not visible on
    // screen
    std::cout << "Enter pin code:";
    std::string password = user_input();

    std::vector<User> users;
    users.emplace_back("DJ", "1111", 1);
    users.emplace_back("BG", "2222", 2);
    users.emplace_back("MJ", "3333", 3);
    users.emplace_back("IA", "4444", 4);
    users.emplace_back("GA", "5555", 5);



      User user("JD","0000",01);
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
