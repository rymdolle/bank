#ifndef BANK_EXCHANGE_MENU_HPP
#define BANK_EXCHANGE_MENU_HPP

#include "menu.hpp"
#include "currency.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

class ExchangeMenu : public Menu
{
private:
User &user_;
int steps = 0;
double amount = 0;
int accIndex = 0;
std::string chosenCurrency;

public:
  ExchangeMenu(User& user) :
    Menu("Exchange"), user_(user)
  {
  }

  void display() override
  {
      std::cout << "Current menu:" << menu << std::endl;

      if (steps == 1) {
          accIndex = menu-1;
          const std::vector<Account>& accounts = user_.getAccounts();
          Account targetAcc = accounts[accIndex];
          std::cout << "  " << std::left << std::setw(30) << targetAcc.getType()
                    << Currency::get(targetAcc.currency).format(targetAcc.getBalance())
                    << '\n'
                    << "  Now chose what amount and hit [Enter] for the next step\n";
          // Add error handling
          amount = menu;
          steps++;
      } else if(steps == 2) {
          int i = 1;
          for (auto& c : Currency::get()) {
              std::cout << std::setw(3) << i++ << '.' << ' ' << c.first << '\n';
          }
          std::cout << "  No choose what currency you want to exchange the chosen amount to.\n"
                    << "  Hit [Enter] to finish\n";
          chosenCurrency = menu;
          steps++;
      } else if (steps == 3) {

          // Add if complete amount was chosen transfer the whole account otherwise create new.
          std::cout << "  You have chosen: " << chosenCurrency << " and you will receive: " << "xxxx.xx\n"
                    << "  based on your original amount: " << amount << std::endl;
      } else {
          int i = 1;
          for (Account& a : user_.getAccounts()) {
              std::cout << "  " << i++ << "." << std::left << std::setw(30) << a.getType()
                        << Currency::get(a.currency).format(a.getBalance())
                        << '\n';
          }
          std::cout    << "  Select what account, amount and unique currency identifier(XXX) \n  "
                       << "all seperated by hitting the [Enter] key" << std::endl;
          steps++;
      }
    int i = 1;
    for (auto& c : Currency::get()) {
      std::cout << std::setw(3) << i++ << '.' << ' ' << c.first << '\n';
    }
  }

  Menu* enter(std::string input) override
  {
    return this;
  }

  size_t size() override
  {
    return Currency::get().size();
  }
};

#endif /* BANK_EXCHANGE_MENU_HPP */
