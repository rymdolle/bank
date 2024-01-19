#include <iostream>

#include "login.hpp"
#include "navigation.hpp"
#include "account.hpp"
#include "user.hpp"

int main(int argc, char *argv[])
{
    // TODO: Generate random accounts from set list of names and numbers?
    // Account creation which is put into account vector
    std::vector<Account> accVec;
    accVec.emplace_back("Savings Account", 1000.10, 1);
    accVec.emplace_back("Regular Account", 2500.25, 1);
    accVec.emplace_back("Salary Account", 300.30, 1);
    accVec.emplace_back("Savings Account", 5000.50, 2);

    // User creation which is put into user vector
    std::vector<User> userVec;
    userVec.emplace_back("JD", "1111", 1);
    userVec.emplace_back("BG", "2222", 2);
    userVec.emplace_back("MJ", "3333", 3);
    userVec.emplace_back("IA", "4444", 4);
    userVec.emplace_back("SL", "5555", 5);

    User currentUser("nan", "0",0);

  std::cout << "Welcome to BANK!\n";
    if (login(currentUser, &userVec)) {
        Navigation nav(currentUser, userVec, accVec);
        nav.run();
    }
    std::cout << "Exiting.\n";

    return 0;
}
