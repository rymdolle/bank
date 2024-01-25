#ifndef BANK_TRANSFER_MENU_HPP
#define BANK_TRANSFER_MENU_HPP

#include "menu.hpp"
#include "user.hpp"
#include "currency.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

class TransferMenu : public Menu
{
private:
  User& user_;
  int account_from;
  int account_to;
  int amount;

  enum class step {
    FROM_ACCOUNT,
    TO_ACCOUNT,
    AMOUNT,
    TRANSFER,
  } state;

public:
  TransferMenu(User& user) :
    Menu("Transfer"), user_(user)
  {
    state = step::FROM_ACCOUNT;
  }

  void display() override
  {
    print_title();

    switch (state) {
    case step::FROM_ACCOUNT: {
      std::cout << "Select an account to transfer from or 0 to abort\n";
      int i = 1;
      for (Account& a : user_.getAccounts()) {
        std::cout << std::right << std::setw(3) << i << ". "
                  << a.getAccountName()
                  << '\n';
        ++i;
      }
      break;
    }
    case step::TO_ACCOUNT: {
      std::cout << "Select an account to transfer to or 0 to abort\n";
      int i = 1;
      for (Account& a : user_.getAccounts()) {
        if (i != account_from) {
          std::cout << std::right << std::setw(3) << i << ". "
                    << a.getAccountName()
                    << '\n';
        }
        ++i;
      }
      break;
    }
    case step::AMOUNT: {
      std::cout << "Select an amount to transfer or 0 to abort\n";
      break;
    }
    case step::TRANSFER: {
      std::cout << "Transfered " << amount
                << " from " << '\''
                << user_.getAccounts()[account_from].getAccountName()
                << '\''
                << " to " << '\''
                << user_.getAccounts()[account_to].getAccountName()
                << '\''
                << '\n';
      std::cout << '\n'
                << "Press [Enter] to go back\n";
    }
    default:
      break;
    }
  }

  Menu* enter(std::string input) override
  {
    if (input == "0") {
      state = step::FROM_ACCOUNT;
      return parent_;
    }

    if (state == step::FROM_ACCOUNT) {
      account_from = std::stoi(input);
      state = step::TO_ACCOUNT ;
    } else if (state == step::TO_ACCOUNT) {
      account_to = std::stoi(input);
      state = step::AMOUNT ;
    } else if (state == step::AMOUNT) {
      amount = std::stoi(input);
      state = step::TRANSFER ;
    } else if (state == step::TRANSFER) {
      return parent_;
    }
    return this;
  }
};

#endif /* BANK_TRANSFER_MENU_HPP */
