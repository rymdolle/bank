#ifndef BANK_TRANSFER_MENU_HPP
#define BANK_TRANSFER_MENU_HPP

#include "menu.hpp"
#include "currency.hpp"
#include <iostream>
#include <map>
#include <string>

class TransferMenu : public Menu
{
private:

public:
  TransferMenu() :
    Menu("Transfer")
  {
  }

  void enter(int menu) override
  {
  }
};

#endif /* BANK_TRANSFER_MENU_HPP */
