#include "navigation.hpp"
#include <iostream>
#include <string>

Navigation::Navigation(User& user)  :
    main_menu(user)
{
}

void Navigation::run()
{
  Menu *current = &main_menu;
  while (current != nullptr) {
    std::string text;
    current->display();
    std::getline(std::cin, text);
    std::cout << '\n';
    current = current->enter(text);
  }
}
