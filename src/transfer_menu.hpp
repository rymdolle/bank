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
  int step;

public:
  TransferMenu(User& user) :
    Menu("Transfer"), user_(user)
  {
    step = 0;
  }

  void display(int menu) override
  {
    std::cout << "Select an account to transfer from\n";
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

  Menu* enter(int menu) override
  {
    std::cout << "Step: " << step << '\n';
    std::cout << "Menu: " << menu << '\n';
    if (menu == 0)
      step = 0;
    return this;
  }

};

#endif /* BANK_TRANSFER_MENU_HPP */
