//account.cpp
#include "account.hpp"
//load from account.tsv data file
std::vector<Account> Account::accounts_ =
  Account::loadFromFile("data/accounts.tsv");
