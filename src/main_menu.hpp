#ifndef BANK_MAIN_MENU_HPP
#define BANK_MAIN_MENU_HPP

#include "menu.hpp"
#include "currency.hpp"
#include <iostream>
#include <map>
#include <string>

class MainMenu : public Menu
{
private:

public:
  MainMenu() :
    Menu("Bank")
  {
  }

  void enter(int menu) override
  {
  }
};

#endif /* BANK_MAIN_MENU_HPP */
