#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <cctype>
#include <string>
#include <vector>
#include <iostream>

#include "menu.hpp"
#include "main_menu.hpp"
#include "user.hpp"

class Navigation
{
private:
    MainMenu main_menu;
public:
  Navigation(User& user);

  void run();
};

#endif /* NAVIGATION_H */
