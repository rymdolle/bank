#ifndef BANK_TRANSFER_MENU_HPP
#define BANK_TRANSFER_MENU_HPP

#include "menu.hpp"
#include "user.hpp"
#include "currency.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

class TransferMenu : public Menu
{
private:
  User& user_;

public:
  TransferMenu(User& user) :
    Menu("Transfer"), user_(user)
  {
  }

  void display() override
  {
    print_title();

    std::cout << '\n'
              << "Select an account to transfer from\n";
    int i = 1;
    for (auto& a : user_.getAccounts()) {
      std::cout << std::setw(3) << i++ << '.' << ' '
                << a.getAccountName()
                << '\n';
    }
  }

  size_t size() override
  {
    return 3;
  }

  Menu* enter(std::string input) override
  {
    std::cout << "Menu: " << input << '\n';
    return this;
  }

};

#endif /* BANK_TRANSFER_MENU_HPP */
