//account.cpp
#include "account.hpp"
//load from account.tsv data file
std::vector<Account> Account::accounts_ =
  Account::loadFromFile("data/accounts.tsv");

void Account::setCurrency(const std::string &currency) {
    currency_ = currency;
}
