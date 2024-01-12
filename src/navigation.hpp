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
    for (size_t i = 0; i < main_options.size(); ++i) {
      std::cout << i+1 << ". " << main_options[i] << '\n';
    }
  }

private:
  std::vector<std::string> main_options
    {
      "Account and balance",
      "Transfer",
      "Exchange",
      "Logout",
    };

  std::vector<std::string> account_options {
    "Back"
  };

  std::vector<std::string> transfer_options {
    "Back"
  };

  std::vector<std::string> exchange_options {
    "Back"
  };

};

#endif /* NAVIGATION_H */
