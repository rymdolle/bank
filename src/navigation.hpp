#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <string>
#include <vector>
#include <iostream>

#include "menu.hpp"
#include "account_menu.hpp"
#include "user.hpp"

class Navigation
{
private:
    Menu main_menu;
    std::vector<Account> &accVec;

  enum MenuID {
    MAIN,
    ACCOUNT,
    TRANSFER,
    EXCHANGE,
  };

public:

  Navigation(std::vector<Account> &accounts) :
    main_menu("Bank", MAIN),
    accVec(accounts) {

    Menu* menu;
    AccountMenu* amenu = new AccountMenu(accounts);
    main_menu.addSubmenu(amenu);

    menu = new Menu("Transfer", TRANSFER);
    main_menu.addSubmenu(menu);

    menu = new Menu("Exchange", EXCHANGE);
    main_menu.addSubmenu(menu);
  }


  void run()
  {
    Menu *current = &main_menu;
    while (current != nullptr) {
      current->display();
      size_t choice;
      std::cin >> choice;
      std::cout << '\n';
      current = current->enter(choice);
      if (!current)
        break;
      switch (current->id) {
      case ACCOUNT: {
        break;
      }
      case TRANSFER:
      case EXCHANGE:
      default:
        break;
      }
    }
  }

};

#endif /* NAVIGATION_H */
