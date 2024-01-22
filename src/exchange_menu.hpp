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

  void enter(int menu) override
  {
    int i = 1;
    std::cout << "EXCHANGE MENU " << menu << '\n';
    for (auto& c : Currency::get()) {
      std::cout << std::setw(3) << i++ << '.' << ' ' << c.first << '\n';
    }
  }

  size_t size() override
  {
    return Currency::get().size();
  }
};

#endif /* BANK_EXCHANGE_MENU_HPP */
