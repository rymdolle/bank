#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>

#include "currency.hpp"

std::map<std::string, Currency> Currency::currencies_{};

Currency::Currency()
{
  entity_ = "UNKNOWN";
  currency_ = "N.A.";
  ncode_ = 0;
  minor_ = 0;
}

Currency::Currency(std::string line)
{
  std::stringstream csv(line);
  std::string value;
  std::getline(csv, entity_, '\t');
  std::getline(csv, currency_, '\t');
  std::getline(csv, acode_, '\t');

  std::getline(csv, value, '\t');
  ncode_ = std::stoi(value);

  std::getline(csv, value, '\t');
  minor_ = std::stoi(value);
}

std::map<std::string, Currency>&  Currency::get()
{
  return currencies_;
}

Currency& Currency::get(std::string acode)
{
  if (currencies_.count(acode) > 0)
    return currencies_[acode];
  return currencies_["XXX"];
}

std::string Currency::format(int64_t amount)
{
  std::stringstream ss;
  ss << acode_;
  if (!acode_.empty())
    ss << ' ';
  ss << amount / pow10_[minor_];
  if (minor_ > 0) {
    ss << '.' << std::setw(minor_) << std::setfill('0')
       << amount % pow10_[minor_];
  }

  return ss.str();
}

void Currency::loadFromFile(std::string filename)
{
  std::ifstream file(filename);
  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    Currency c(line);
    currencies_[c.acode_] = c;
  }
}
