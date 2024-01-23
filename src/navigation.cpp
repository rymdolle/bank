#include "navigation.hpp"
#include <iostream>

Navigation::Navigation(User& user)  :
    main_menu(user)
{
}

void Navigation::run()
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
