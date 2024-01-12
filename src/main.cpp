#include <iostream>
#include "login.hpp"
#include "navigation.hpp"

int main(int argc, char *argv[])
{
  std::cout << "Welcome to BANK!\n";
  login();
  Navigation nav;
  nav.display();
  return 0;
}
