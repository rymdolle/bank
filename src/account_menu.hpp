#ifndef BANK_ACCOUNT_MENU_HPP
#define BANK_ACCOUNT_MENU_HPP

#include "menu.hpp"
#include "account.hpp"
#include "currency.hpp"
#include <iostream>
#include <string>

class AccountMenu : public Menu
{
private:
  std::vector<Account> &accVec;

public:
  AccountMenu(std::vector<Account> &accounts) :
    Menu("Accounts", -1),
    accVec(accounts)
  {
  }

  void display() override
  {
    // Print menu title
    std::cout << title << '\n';
    for (size_t i = 0; i < title.length(); ++i)
      std::cout << '=';
    std::cout << '\n';

    // Print numbered menu options
    std::cout << "  " <<  std::left << std::setw(30) << "Type:"
              << "Balance:\n";
    for (Account& a : accVec) {
      std::cout << "  " << std::left << std::setw(30) << a.getType()
                << Currency::get(a.currency).format(a.getBalance())
                << '\n';
    }

    // Checks if item has a parent menu and add exit or back
    std::cout << '\n'
              << std::right << std::setw(3) << 0 << ". Back" << std::endl;
  }
};

#endif /* BANK_ACCOUNT_MENU_HPP */
