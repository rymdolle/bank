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

bool login()
{
  int count = 0;
  do {
    std::cout << "Enter username:";
    std::string username = user_input();
    // TODO: add password masking so user password is not visible on
    // screen
    std::cout << "Enter pin code:";
    std::string password = user_input();

    // TODO: Generate random accounts from set list of names and numbers?
    // TODO: Move to respective classes?
    // Account creation and addition to user vector
    Account::accVec.emplace_back("Savings Account", 1000.0, 1);
    Account::accVec.emplace_back("Savings Account", 1000.0, 1);
    Account::accVec.emplace_back("Regular Account", 2500.0, 1);
    Account::accVec.emplace_back("Salary Account", 300.0, 1);

    // User creation and addition to user vector
    User::userVec.emplace_back("JD", "1111", 1);
    User::userVec.emplace_back("BG", "2222", 2);
    User::userVec.emplace_back("MJ", "3333", 3);
    User::userVec.emplace_back("IA", "4444", 4);
    User::userVec.emplace_back("GA", "5555", 5);

      for (const auto& user : User::userVec) {
          if (user.verify(username, password)) {
              std::cout << "\nLogin successful.\n"
                        << "Welcome " << username << "!\n\n";
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
