//transfer_menu.hpp
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
  int account_src;
  int account_dst;
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

  //transaction menu
  void display() const override
  {
    print_title();

    switch (state) {
    case step::FROM_ACCOUNT: {//from account
      std::cout << "Select an account to transfer from or 0 to abort\n";
      int i = 1;
      for (Account& a : user_.getAccounts()) {
        std::cout << std::right << std::setw(3) << i << ". "
                  << std::left << std::setw(30) << a.getAccountName()
                  << Currency::get(a.getCurrency()).format(a.getBalance())
                  << '\n';
        ++i;
      }
      std::cout << std::right << std::setw(3) << 0 << ". Abort\n";
      break;
    }
    case step::TO_ACCOUNT: {//to account
      std::cout << "Select an account to transfer to or 0 to abort\n";
      int i = 1;
      for (Account& a : user_.getAccounts()) {
        if (i != account_src) {
          std::cout << std::right << std::setw(3) << i << ". "
                    << std::left << std::setw(30) << a.getAccountName()
                    << Currency::get(a.getCurrency()).format(a.getBalance())
                    << '\n';
        }
        ++i;
      }
      std::cout << std::right << std::setw(3) << 0 << ". Abort\n";
      break;
    }
    case step::AMOUNT: {// amount
      std::cout << "Select an amount to transfer or 0 to abort\n"
                << std::right << std::setw(3) << 0 << ". Abort\n";
      break;
    }
    case step::TRANSFER: {//transaction
      std::string currency = user_.getAccounts()[account_src - 1].getCurrency();
      std::cout << "Transferred " << Currency::get(currency).format(amount)
                << " from " << '\''
                << user_.getAccounts()[account_src - 1].getAccountName()
                << '\''
                << " to " << '\''
                << user_.getAccounts()[account_dst - 1].getAccountName()
                << '\''
                << '\n';
      std::cout << '\n'
                << "Press [Enter] to go back\n";
      break;
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

    switch (state) {
    case step::FROM_ACCOUNT: {
      account_src = std::atoi(input.c_str());
      if (account_src < 1 || account_src > user_.getAccounts().size()) {
        std::cout << "Invalid account source.\n";
        break;
      }
      state = step::TO_ACCOUNT;
      break;
    }
    case step::TO_ACCOUNT: {
      account_dst = std::atoi(input.c_str());
      if (account_dst < 1 ||
          account_dst > user_.getAccounts().size() ||
          account_dst == account_src) {
        std::cout << "Invalid account destination.\n";
        break;
      }
      Account& src = user_.getAccounts()[account_src - 1];
      Account& dst = user_.getAccounts()[account_dst - 1];
      if (src.getCurrency() != dst.getCurrency()) {
        std::cout << "Source and destination currencies does not match.\n";
        break;
      }
      state = step::AMOUNT;
      break;
    }
    case step::AMOUNT: {
      Account& src = user_.getAccounts()[account_src - 1];
      Account& dst = user_.getAccounts()[account_dst - 1];
      std::string currency = src.getCurrency();
      amount = Currency::get(currency).parse(input);
      if (amount > 0 && amount <= src.getBalance()) {
        src.setBalance(src.getBalance() - amount);
        dst.setBalance(dst.getBalance() + amount);
      } else {
        std::cout << "Cannot transfer funds. Invalid amount."
                  <<"\n\n";
        break;
      }
      state = step::TRANSFER;
      break;
    }
    case step::TRANSFER: {
      state = step::FROM_ACCOUNT;
      return parent_;
    }
    default:
      break;
    }
    return this;
  }
};

#endif /* BANK_TRANSFER_MENU_HPP */
