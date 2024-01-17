#ifndef BANK_MENU_HPP
#define BANK_MENU_HPP

#include <iomanip>
#include <string>
#include <vector>
#include <iostream>

#include "account.hpp"

class Menu {
public:
  const int id;
  const std::string title;

private:
  Menu *parent_;
  std::vector<Menu*> options;
  void *data;

public:
  Menu(std::string name) : Menu(name, -1) {}
  Menu(std::string name, int id) :
    id(id), title(name)
  {
    parent_ = nullptr;
  }

  ~Menu()
  {
    // Delete all submenus
    for (auto item : options)
      delete item;
  }


    void display()
    {
      // Print menu title
      std::cout << title << '\n';
      for (size_t i = 0; i < title.length(); ++i)
        std::cout << '=';
      std::cout << '\n';

      // Print numbered menu options
      for (size_t i = 0; i < options.size(); ++i) {
        std::cout << std::setw(3) << i+1 << ". " << options[i]->title << '\n';
      }

      // Checks if item has a parent menu and add exit or back
      if (parent_ != nullptr)
        std::cout << std::setw(3) << 0 << ". Back" << std::endl;
      else
        std::cout << std::setw(3) << 0 << ". Logout" << std::endl;
    }

    Menu* enter(size_t submenu) {
      if (submenu == 0) // Back or exit
        return parent_;

      if (submenu > options.size()) {
        std::cerr << "Invalid submenu\n";
        // return current menu
        return this;
      }

      return options[submenu - 1];
    }

    void addItem(const std::string& name) {
      Menu* item = new Menu(name);
      item->parent_ = this;
      options.push_back(item);
    }

  void addSubmenu(Menu* sub)
  {
    sub->parent_ = this;
    options.push_back(sub);
  }

};

#endif //BANK_MENU_HPP
