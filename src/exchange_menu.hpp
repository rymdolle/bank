#ifndef BANK_EXCHANGE_MENU_HPP
#define BANK_EXCHANGE_MENU_HPP

#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include "menu.hpp"
#include "currency.hpp"

class ExchangeMenu : public Menu
{
private:
User &user_;
int step = 0;
double amount = 0;
int accIndex = 0;
std::string chosenCurrency;
std::string userInputStr;
int userInputInt;
std::string targetCurrency;
double targetAmount = 0;

public:

    ExchangeMenu(User& user) :
    Menu("Exchange"), user_(user)
  {
  }

  void display() override
  {
      if (step == 1) {
          // Grabs the input from the user and assigns it to accIndex
          accIndex = userInputInt;

          // Get the logged users account and assign it to a vector for processing
          const std::vector<Account>& accounts = user_.getAccounts();
          Account targetAcc = accounts[accIndex-1];
          // Save the chosen accounts currency and balance
          targetCurrency = targetAcc.getCurrency();
          targetAmount = targetAcc.getBalance();
          // Prompt for the users input
          std::cout << "  " << std::left << std::setw(30) << targetAcc.getAccountName()
                    << Currency::get(targetAcc.getCurrency()).format(targetAcc.getBalance())
                    << '\n'
                    << "  Now chose what amount and hit [Enter] for the next step\n";
          // Save the users input as the desired amount
          amount = userInputInt;
      } else if(step == 2) {

          // Prints the currency choices in a grid
          int cols = 9;
          int size = Currency::get().size();
          int i = 1;
          for (auto& c : Currency::get()) {
              std::cout << std::setw(3) << ' ' << std::setw(4) << c.first;

              if (i % cols == 0 || i == size) {
                  std::cout << '\n';
              } else {
                  std::cout << '\t';
              }
              i++;
          }
          // Prompts the user for a choice
          std::cout << "\n  Now enter the desired currency from the list\n"
                    << "  Hit [Enter] to finish\n";

      } else if (step == 3) {
          // Choice is saved in chosenCurrency
          chosenCurrency = userInputStr;
          // Loops through the currency map to find the chosen currency
          int i = 0;
          for (auto& c : Currency::get()) {
              i++;
              if (i == userInputInt) {
                  chosenCurrency = c.first;
              }
          }

          // Add if complete amount was chosen transfer the whole account otherwise create new.


          std::cout << "  The chosen amount of " << targetCurrency << " " << amount << " will be exchanged to "
                    << chosenCurrency << " " << "INSERT_END_RESULT\n";
          step = 0;
      } else {

          int i = 1;
          for (Account& a : user_.getAccounts()) {
              std::cout << "  " << i++ << "." << std::left << std::setw(30) << a.getAccountName()
                        << Currency::get(a.getCurrency()).format(a.getBalance())
                        << '\n';

          }
          std::cout    << "  Select what account you would to exchange from,\n"
                          "  if you at any point would like to abort,\n"
                          "  clear the textbox,type 0 and press [Enter]\n";
      }
  }

  Menu* enter(std::string input) override
  {
      if (!input.empty() && isdigit(input[0])){
          userInputInt = std::stoi(input);
      } else {
          std::transform(input.begin(), input.end(), input.begin(), ::toupper);
          userInputStr = input;
      }
      std::cout << "\nThis is the target amount " << targetAmount;
      std::cout << "\nThis is step: " << step << "\n";
      // TODO: Replace with currey parse function
      if (userInputInt*100 > targetAmount && step == 1) {
          std::cout << "Amount exceeds your balance, please try again.\n";
          step = 1;
          return this;
      }

      if (userInputInt == 0) {
          std::cout << "\nThe operation has been aborted, try again.\n";
          return parent_;
      }
      step++;
    return this;
  }
};

#endif /* BANK_EXCHANGE_MENU_HPP */
