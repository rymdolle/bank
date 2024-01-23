#include "account.hpp"

std::vector<Account> Account::accounts_ =
  Account::loadFromFile("data/accounts.tsv");
