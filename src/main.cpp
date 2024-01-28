//main.cpp
#include <iostream>
#include "login.hpp"
#include "navigation.hpp"
#include "account.hpp"
#include "user.hpp"
#include "currency.hpp"

int main(int argc, char *argv[])
{
  // Load currencies
  Currency::loadFromFile("data/currency.tsv");
  // Load accounts
  Account::loadFromFile("data/accounts.tsv");

    User currentUser;
  //greeting the user to the account
  std::cout << "Welcome to BANK!\n";
  while (login(currentUser)) {
      Navigation nav(currentUser);// navigation in the bank account
        nav.run();
    }
    std::cout << "Exiting.\n";

    return 0;
}
