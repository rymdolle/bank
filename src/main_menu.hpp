#ifndef BANK_MAIN_MENU_HPP
#define BANK_MAIN_MENU_HPP

#include "menu.hpp"
#include "user.hpp"
#include "currency.hpp"
#include "account_menu.hpp"
#include "transfer_menu.hpp"
#include "exchange_menu.hpp"
#include <cstddef>
#include <iostream>
#include <map>
#include <string>

class MainMenu : public Menu
{
private:
  std::vector<Menu*> options_;
public:
  MainMenu(User& user) :
    Menu("Bank")
  {
    addSubmenu(new AccountMenu(user));
    addSubmenu(new TransferMenu(user));
    addSubmenu(new ExchangeMenu(user));
  }

  Menu* enter(std::string input) override
  {
    int choice = 0;
    if (!input.empty() && std::isdigit(input[0])) {
      choice = std::stoi(input);
    } else {
      std::cout << "Invalid input\n";
      return this;
    }
    if (choice == 0) // Back or exit
      return parent_;

    if (choice > options_.size()) {
      std::cout << "Invalid input\n";
      // return current menu
      return this;
    }

    return options_[choice - 1];
  }

  void display() override
  {
    print_title();

    // Print numbered menu options
    for (size_t i = 0; i < options_.size(); ++i) {
      std::cout << std::right << std::setw(3) << i+1 << ". "
                << options_[i]->title << '\n';
    }

    std::cout << std::right << std::setw(3) << 0 << ". Logout" << std::endl;
  }

  void addSubmenu(Menu *sub)
  {
    sub->setParent(this);
    options_.push_back(sub);
  }
};

#endif /* BANK_MAIN_MENU_HPP */
