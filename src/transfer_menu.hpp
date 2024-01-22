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

  void display(int menu) override
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

};

#endif /* BANK_TRANSFER_MENU_HPP */
