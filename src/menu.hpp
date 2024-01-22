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
  int selected;
  std::vector<Menu*> options;

public:
  Menu(std::string name) :
    title(name)
  {
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
  virtual void enter() = 0;

  void display()
  {
    print_title();

    // Print numbered menu options
    for (size_t i = 0; i < options.size(); ++i) {
      std::cout << std::setw(3) << i+1 << ". "
                << options[i]->title << '\n';
    }

    // Call virtual enter function
    enter();

    // Checks if item has a parent menu and add exit or back
    if (parent_ != nullptr)
      std::cout << std::right << std::setw(3) << 0 << ". Back" << std::endl;
    else
      std::cout << std::right << std::setw(3) << 0 << ". Logout" << std::endl;
  }

  Menu* select(size_t submenu) {
    if (submenu == 0) // Back or exit
      return parent_;

    if (submenu > options.size()) {
      std::cerr << "Invalid submenu\n";
      // return current menu
      return this;
    }

    selected = submenu;
    return options[submenu - 1];
  }

  void addSubmenu(Menu *sub)
  {
    sub->parent_ = this;
    options.push_back(sub);
  }
};

#endif //BANK_MENU_HPP
