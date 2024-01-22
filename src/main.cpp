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

    User currentUser("nan", "0",0);

  std::cout << "Welcome to BANK!\n";
    if (login(currentUser)) {
      Navigation nav(currentUser);
        nav.run();
    }
    std::cout << "Exiting.\n";

    return 0;
}
