#ifndef BANK_MENU_HPP
#define BANK_MENU_HPP

#include <string>
#include <vector>
#include <iostream>

class Menu {
public:

  enum class ID {
    MAIN,
    ACCOUNT,
    TRANSFER,
    EXCHANGE,
    NONE = -1,
  };

private:
  Menu *parent_;
  std::string title_;
  std::vector<Menu*> options;
  Menu::ID id_;

public:
    Menu(std::string name, Menu::ID id)
    {
      parent_ = nullptr;
      title_ = name;
      id_ = id;
    }

  ~Menu()
  {
    // Delete all submenus
    for (auto item : options)
      delete item;
  }


    void display()
    {
      std::cout << title_ << '\n';
      for (size_t i = 0; i < title_.length(); ++i)
        std::cout << '=';
      std::cout << '\n';

      for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i+1 << ". " << options[i]->title_ << '\n';
      }

      // Checks if item has a parent menu and add exit or back
      if (parent_ != nullptr)
        std::cout << "0. Back" << std::endl;
      else
        std::cout << "0. Exit" << std::endl;
    }

    Menu* enter(size_t submenu) {
      if (submenu == 0) // Back or exit
        return parent_;

      if (submenu > options.size()) {
        std::cout << "Invalid submenu\n";
        // return current menu
        return this;
      }

      return options[submenu - 1];
    }

    void addItem(const std::string& name) {
      Menu* item = new Menu(name, Menu::ID::NONE);
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
