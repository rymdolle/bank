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

    // Account creation which is put into account vector
    std::vector<Account> accVec;
    accVec.emplace_back("Savings Account", 1000.10, 1);
    accVec.emplace_back("Regular Account", 2500.25, 1);
    accVec.emplace_back("Salary Account", 300.30, 1);
    accVec.emplace_back("Savings Account", 5000.50, 2);

    User currentUser("nan", "0",0);

  std::cout << "Welcome to BANK!\n";
    if (login(currentUser)) {
        Navigation nav(currentUser, accVec);
        nav.run();
    }
    std::cout << "Exiting.\n";

    return 0;
}
