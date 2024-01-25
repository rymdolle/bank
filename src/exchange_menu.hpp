#ifndef BANK_EXCHANGE_MENU_HPP
#define BANK_EXCHANGE_MENU_HPP

#include "menu.hpp"
#include "currency.hpp"
#include <iomanip>
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

  void display() override
  {
    int i = 1;
    for (auto& c : Currency::get()) {
      std::cout << std::setw(3) << i++ << '.' << ' ' << c.first << '\n';
    }
  }

  Menu* enter(std::string input) override
  {
    return this;
  }
};

#endif /* BANK_EXCHANGE_MENU_HPP */
