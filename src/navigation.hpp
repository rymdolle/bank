#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <string>
#include <vector>
#include <iostream>
#include "menu.hpp"

class Navigation
{
private:
    Menu main_menu;

  enum MenuID {
    MAIN,
    ACCOUNT,
    TRANSFER,
    EXCHANGE,
  };

public:

  Navigation() :
    main_menu("Bank", MAIN)
  {
    Menu* menu;
    menu = new Menu("Account and balance", ACCOUNT);
    menu->addItem("Salary account");
    menu->addItem("Savings account");
    main_menu.addSubmenu(menu);

    menu = new Menu("Transfer", TRANSFER);
    main_menu.addSubmenu(menu);

    menu = new Menu("Exchange", EXCHANGE);
    main_menu.addSubmenu(menu);
  }


  void run()
  {
    // std::vector<std::string> *current_menu = &main_options;
    // std::vector<std::string> *previous_menu = nullptr;
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
      case ACCOUNT:
      case TRANSFER:
      case EXCHANGE:
      default:
        break;
      }
    }
  }

};

#endif /* NAVIGATION_H */
