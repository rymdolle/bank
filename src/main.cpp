//main.cpp
#include <iostream>
#include "login.hpp"
#include "account.hpp"
#include "user.hpp"
#include "currency.hpp"
#include "main_menu.hpp"

int main(int argc, char *argv[])
{
  User user;
  std::cout << "Welcome to BANK!\n";
  while (login(user)) {
    MainMenu main_menu(user);
    Menu *current = &main_menu;
    while (current != nullptr) {
      std::string text;
      current->display();
      std::getline(std::cin, text);
      std::cout << '\n';
      current = current->enter(text);
    }
  }
  std::cout << "Exiting.\n";

  return 0;
}
