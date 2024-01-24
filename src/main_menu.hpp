#ifndef BANK_MAIN_MENU_HPP
#define BANK_MAIN_MENU_HPP

#include "menu.hpp"
#include "user.hpp"
#include "currency.hpp"
#include "account_menu.hpp"
#include "transfer_menu.hpp"
#include "exchange_menu.hpp"
#include <cstddef>
#include <iostream>
#include <map>
#include <string>

class MainMenu : public Menu
{
private:
public:
  MainMenu(User& user) :
    Menu("Bank")
  {
    addSubmenu(new AccountMenu(user));
    addSubmenu(new TransferMenu(user));
    addSubmenu(new ExchangeMenu());
  }

  void display(int menu) override
  {
  }
};

#endif /* BANK_MAIN_MENU_HPP */
