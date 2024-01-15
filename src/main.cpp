#include <iostream>
#include "login.hpp"
#include "navigation.hpp"

int main(int argc, char *argv[])
{
  std::cout << "Welcome to BANK!\n";
  if (login()) {
    Navigation nav;
    nav.run();
  }
  std::cout << "Exit.\n";
  return 0;
}
