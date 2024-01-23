#ifndef BANK_ACCOUNT_MENU_HPP
#define BANK_ACCOUNT_MENU_HPP

#include "menu.hpp"
#include "user.hpp"
#include "account.hpp"
#include "currency.hpp"
#include <iostream>
#include <string>

class AccountMenu : public Menu
{
private:
  User& user_;

public:
  AccountMenu(User& user) :
    Menu("Accounts"), user_(user)
  {
  }

  size_t size() override
  {
    return 0;
  }

  Menu* enter(int menu) override
  {
    return this;
  }

  void display(int menu) override
  {
    // Print numbered menu options
    std::cout << "  " <<  std::left << std::setw(30) << "Type:"
              << "Balance:\n";
    for (Account& a : user_.getAccounts()) {
      std::cout << "  " << std::left << std::setw(30) << a.getAccountName()
                << Currency::get(a.getCurrency()).format(a.getBalance())
                << '\n';
    }
  }
};

#endif /* BANK_ACCOUNT_MENU_HPP */
