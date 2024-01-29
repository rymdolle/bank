//menu.hpp
#ifndef BANK_MENU_HPP
#define BANK_MENU_HPP

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "account.hpp"

class Menu {
public:
  const std::string title;

protected:
  Menu *parent_;

public:
  Menu(std::string name) :
    title(name)
  {
    parent_ = nullptr;
  }

  virtual ~Menu() {}
  //print punts menu
  void print_title() const
  {
    // Print menu title
    std::cout << title << '\n';
    for (size_t i = 0; i < title.length(); ++i)
      std::cout << '=';
    std::cout << '\n';
  }


  // Virtual function that has to be implemented
  virtual Menu* enter(std::string input) = 0;
  virtual void display() const = 0;

  void setParent(Menu* parent)
  {
    parent_ = parent;
  }
};

#endif //BANK_MENU_HPP
