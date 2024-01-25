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
int step = 0;
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

      if (step == 1) {
          accIndex = menu;
          const std::vector<Account>& accounts = user_.getAccounts();
          Account targetAcc = accounts[accIndex-1];
          std::cout << "  " << std::left << std::setw(30) << targetAcc.getType()
                    << Currency::get(targetAcc.currency).format(targetAcc.getBalance())
                    << '\n'
                    << "  Now chose what amount and hit [Enter] for the next step\n";
          // Add error handling
          step++;
      } else if(step == 2) {
          amount = menu;
          int i = 1;
          for (auto& c : Currency::get()) {
              std::cout << std::setw(3) << i++ << '.' << ' ' << c.first << '\n';
          }
          std::cout << "  No choose what currency you want to exchange the chosen amount to.\n"
                    << "  Hit [Enter] to finish\n";
          step++;
      } else if (step == 3) {
          chosenCurrency = std::to_string(menu);
          std::cout << "This is the chosen currency: " << chosenCurrency<< std::endl;

          int i = 0;
          for (auto& c : Currency::get()) {
              i++;
              if (i == menu) {
                  chosenCurrency = c.first;
              }
          }
          // Needs currency data
          // Add if complete amount was chosen transfer the whole account otherwise create new.
          std::cout << "  The chosen amount of " << amount << " will be exchanged to " << chosenCurrency << " INSERT_END_RESULT\n";
          step = 0;
      } else {
          int i = 1;
          for (Account& a : user_.getAccounts()) {
              std::cout << "  " << i++ << "." << std::left << std::setw(30) << a.getType()
                        << Currency::get(a.currency).format(a.getBalance())
                        << '\n';

          }
          std::cout    << "  Select what account, amount and unique currency identifier(XXX) \n  "
                       << "all seperated by hitting the [Enter] key" << std::endl;
          step++;
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
