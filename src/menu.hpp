#ifndef BANK_MENU_HPP
#define BANK_MENU_HPP

#include <string>
#include <vector>
#include <iostream>

class Menu {

    std::vector<std::string> options;
    std::vector<Menu> sub_menu;
    int id;

public:
    Menu()
    {
      std::string name;
    }


    void display()
    {
      for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i+1 << ". " << options[i] << '\n';
      }

      // Checks if last item is not "Logout", if true replace with back instead
      if (options.back() != "Logout")
        std::cout << options.size()+1 << ". Back" << std::endl;
    }

    void menu_action(int action) {
      options[action];
    }

    void addItem(const std::string& string) {
      options.push_back(string);
    }
};

#endif //BANK_MENU_HPP
