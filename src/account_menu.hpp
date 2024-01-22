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
  std::vector<Account> &accounts_;

public:
  AccountMenu(std::vector<Account> &accounts) :
    Menu("Accounts"),
    accounts_(accounts)
  {
  }

  void enter() override
  {
    // Print numbered menu options
    std::cout << "  " <<  std::left << std::setw(30) << "Type:"
              << "Balance:\n";
    for (Account& a : accounts_) {
      std::cout << "  " << std::left << std::setw(30) << a.getType()
                << Currency::get(a.currency).format(a.getBalance())
                << '\n';
    }
  }
};

#endif /* BANK_ACCOUNT_MENU_HPP */
