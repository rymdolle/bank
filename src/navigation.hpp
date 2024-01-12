#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <string>
#include <vector>
#include <iostream>

class Navigation
{
public:
  void display()
  {
    for (size_t i = 0; i < options.size(); ++i) {
      std::cout << i+1 << ". " << options[i] << '\n';
    }
  }

private:
  std::vector<std::string> options
    {
      "Account and balance",
      "Transfer",
      "Exchange",
      "Logout",
    };
};

#endif /* NAVIGATION_H */
