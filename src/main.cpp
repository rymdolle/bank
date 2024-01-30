//main.cpp
#include <iostream>
#include "login.hpp"
#include "account.hpp"
#include "user.hpp"
#include "currency.hpp"
#include "main_menu.hpp"

#include "database.hpp"

int main(int argc, char *argv[])
{
  Database db;
  // db.host = "localhost";
  // db.port = "3306";
  // db.database = "bank";
  // db.username = "chas";
  // db.password = "secret";

  if (!db.connect()) {
    std::cerr << "Could not connect to database.\n";
    exit(1);
  }

  for (auto& user : db.users()) {
    std::cout << user.getName() << '\n';
  }

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
