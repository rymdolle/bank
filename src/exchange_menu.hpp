#ifndef BANK_EXCHANGE_MENU_HPP
#define BANK_EXCHANGE_MENU_HPP

#include "menu.hpp"
#include "currency.hpp"
#include <iostream>
#include <map>
#include <string>

class ExchangeMenu : public Menu
{
private:

public:
  ExchangeMenu() :
    Menu("Exchange")
  {
  }

  void enter() override
  {
  }
};

#endif /* BANK_ACCOUNT_MENU_HPP */
