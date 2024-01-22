#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <string>
#include <vector>
#include <iostream>

#include "menu.hpp"
#include "main_menu.hpp"
#include "exchange_menu.hpp"
#include "account_menu.hpp"
#include "transfer_menu.hpp"
#include "user.hpp"

class Navigation
{
private:
    MainMenu main_menu;
    std::vector<Account> &accounts_;

public:

  Navigation(std::vector<Account> &accounts) :
    main_menu(),
    accounts_(accounts) {

    main_menu.addSubmenu(new AccountMenu(accounts));

    main_menu.addSubmenu(new TransferMenu());

    main_menu.addSubmenu(new ExchangeMenu());
  }

  void run()
  {
    Menu *current = &main_menu;
    while (current != nullptr) {
      current->display();
      size_t choice;
      std::cin >> choice;
      std::cout << '\n';
      current = current->select(choice);
    }
  }

};

#endif /* NAVIGATION_H */
