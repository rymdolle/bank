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
    accVec.emplace_back("Savings Account", 1000'10, 1000);
    accVec.emplace_back("Regular Account", 2500'25, 1000);
    accVec.emplace_back("Salary Account", 300'30, 1000);
    accVec.emplace_back("Savings Account", 5000'50, 1001);

    User currentUser("nan", "0",0);

  std::cout << "Welcome to BANK!\n";
    if (login(currentUser)) {
      std::vector<Account> currentAccVec;
      for (Account& a : accVec) {
        if (a.getId() == currentUser.getId()) {
          currentAccVec.emplace_back(a);
        }
      }
        Navigation nav(currentAccVec);
        nav.run();
    }
    std::cout << "Exiting.\n";

    return 0;
}
