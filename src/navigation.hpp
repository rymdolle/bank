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
    Menu account_menu;
    Menu transfer_menu;
    Menu exchange_menu;

public:

    Navigation() {
      main_menu.addItem("Account and balance");
      main_menu.addItem("Transfer");
      main_menu.addItem("Exchange");
      main_menu.addItem("Logout");

      account_menu.addItem("Savings account");

      transfer_menu.addItem("Transfer");

      exchange_menu.addItem("Exchange");
    }


  void run()
  {
    bool running = true;
    // std::vector<std::string> *current_menu = &main_options;
    // std::vector<std::string> *previous_menu = nullptr;
    main_menu.display();
    while(running) {
      size_t choice;
      std::cin >> choice;
      // Check if choice is last item in the menu
      // TODO: Add a menu of menus
      switch (choice-1) {
      case 0:
        account_menu.display();
        break;
      case 1:
        transfer_menu.display();
        break;
      case 2:
        exchange_menu.display();
        break;
      default:
        std::cout << "Invalid choice\n";
        running = false;
        break;
      }
    }

    std::cout << "Exit\n";
  }

};

#endif /* NAVIGATION_H */
