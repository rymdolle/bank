#ifndef BANK_MENU_HPP
#define BANK_MENU_HPP

#include <iomanip>
#include <string>
#include <vector>
#include <iostream>

#include "account.hpp"

class Menu {
public:
  const std::string title;

private:
  Menu *parent_;
  std::vector<Menu*> options;
  int id_;

public:
  Menu(std::string name) :
    title(name)
  {
    id_ = 0;
    parent_ = nullptr;
  }

  virtual ~Menu()
  {
    // Delete all submenus
    for (auto item : options)
      delete item;
  }

  void print_title()
  {
    // Print menu title
    std::cout << title << '\n';
    for (size_t i = 0; i < title.length(); ++i)
      std::cout << '=';
    std::cout << '\n';
  }

  // Virtual function that has to be implemented
  virtual void enter(int menu) = 0;

  void display()
  {
    print_title();

    enter(id_);

    // Print numbered menu options
    for (size_t i = 0; i < options.size(); ++i) {
      std::cout << std::setw(3) << i+1 << ". "
                << options[i]->title << '\n';
    }

    // Checks if item has a parent menu and add exit or back
    if (parent_ != nullptr)
      std::cout << std::right << std::setw(3) << 0 << ". Back" << std::endl;
    else
      std::cout << std::right << std::setw(3) << 0 << ". Logout" << std::endl;
  }

  Menu* select(size_t submenu) {
    id_ = submenu;
    if (submenu == 0) // Back or exit
      return parent_;

    if (submenu > options.size()) {
      // return current menu
      return this;
    }

    return options[submenu - 1];
  }

  void addSubmenu(Menu *sub)
  {
    sub->parent_ = this;
    options.push_back(sub);
  }
};

#endif //BANK_MENU_HPP
