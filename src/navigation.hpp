#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <string>
#include <vector>
#include <iostream>

class Navigation
{
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

public:
  void display(std::vector<std::string> &menu)
  {
    for (size_t i = 0; i < menu.size(); ++i) {
      std::cout << i+1 << ". " << menu[i] << '\n';
    }
  }

  void run()
  {
    bool running = true;
    // std::vector<std::string> *current_menu = &main_options;
    // std::vector<std::string> *previous_menu = nullptr;
    display(main_options);
    while(running) {
      size_t choice;
      std::cin >> choice;
      // Check if choice is last item in the menu
      switch (choice-1) {
      case 0:
        display(account_options);
        break;
      case 1:
        display(transfer_options);
        break;
      case 2:
        display(exchange_options);
        break;
      default:
        std::cout << "Invalid choice\n";
        running = false;
        break;
      }
    }

    std::cout << "Exit\n";
  }

};

#endif /* NAVIGATION_H */
