#include "account.hpp"

std::vector<Account> Account::accounts_ =
  Account::loadFromFile("data/accounts.tsv");

void Account::setCurrency(const std::string &currency) {
    currency_ = currency;
}
