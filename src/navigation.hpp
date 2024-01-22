#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <cctype>
#include <string>
#include <vector>
#include <iostream>

#include "menu.hpp"
#include "main_menu.hpp"
#include "user.hpp"

class Navigation
{
private:
    MainMenu main_menu;
public:
  Navigation(User& user) :
    main_menu(user)
  {
  }

  void run()
  {
    Menu *current = &main_menu;
    while (current != nullptr) {
      current->display();
      std::string text;
      std::getline(std::cin, text);
      std::cout << '\n';
      if (!text.empty() && std::isdigit(text[0])) {
        int choice = std::stoi(text);
        current = current->select(choice);
      } else {
        std::cout << "Invalid input\n";
      }
    }
  }

};

#endif /* NAVIGATION_H */
