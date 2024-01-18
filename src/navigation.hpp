#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <string>
#include <vector>
#include <iostream>

#include "menu.hpp"
#include "user.hpp"

class Navigation
{
private:
    Menu main_menu;
    User &currentUser;
    std::vector<Account> &accVec;

  enum MenuID {
    MAIN,
    ACCOUNT,
    TRANSFER,
    EXCHANGE,
  };

public:

  Navigation(User &loggedUser, std::vector<Account> &accounts) :
    main_menu("Bank", MAIN),
    currentUser(loggedUser),
    accVec(accounts) {

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


    void showUserAccounts(const std::vector<Account> &accounts) {
        // Grabs the corresponding userId to link to accId
        int targetId = currentUser.getId();

        // Prints out the accounts depending on what the currentUsers ID is
        std::cout << "\tType:" << "\t\t\t\tAmount(Sek):\n";
        for (const auto &Account : accVec) {
            if (Account.getId() == targetId) {
                std::cout << "\t" << Account.getType() << "\t\t\t" << Account.getBalance() << "\n";
            }
        }
        std::cout << "\n";
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
          showUserAccounts(accVec);
      case TRANSFER:
      case EXCHANGE:
      default:
        break;
      }
    }
  }

};

#endif /* NAVIGATION_H */
