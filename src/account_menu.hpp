//account_menu.hpp
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

  Menu* enter(std::string input) override
  {
    if (input.empty())
      return parent_;
    return this;
  }
  //displaying account information on the screen - menu
  void display() override
  {
    print_title();

    // Print numbered menu options
    std::cout << "  " <<  std::left << std::setw(30) << "Type:"
              << "Balance:\n";
    int total = 0;
    for (Account& a : user_.getAccounts()) {
      std::cout << "  " << std::left << std::setw(30) << a.getAccountName()
                << Currency::get(a.getCurrency()).format(a.getBalance())
                << '\n';
      total += a.getBalance();
    }

    std::cout << '\n'
              << "Press [Enter] to go back\n";
  }
};

#endif /* BANK_ACCOUNT_MENU_HPP */
