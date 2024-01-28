//navigation.hpp
#include "navigation.hpp"
#include <iostream>
#include <string>

Navigation::Navigation(User& user)  :
    main_menu(user)
{
}
//navigation between punts menu
void Navigation::run()
{
  Menu *current = &main_menu;
  std::string text;
  while (current != nullptr) {
    current->display();
    std::getline(std::cin, text);
    std::cout << '\n';
    current = current->enter(text);
  }
}
