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

public:

  Navigation() :
    main_menu("Bank", Menu::ID::MAIN)
  {
    Menu* account_menu = new Menu("Account and balance", Menu::ID::ACCOUNT);
    account_menu->addItem("Salary account");
    account_menu->addItem("Savings account");
    main_menu.addSubmenu(account_menu);

    Menu* transfer_menu = new Menu("Transfer", Menu::ID::TRANSFER);
    main_menu.addSubmenu(transfer_menu);

    Menu* exchange_menu = new Menu("Exchange", Menu::ID::EXCHANGE);
    main_menu.addSubmenu(exchange_menu);
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
    }

    std::cout << "Exit.\n";
  }

};

#endif /* NAVIGATION_H */
