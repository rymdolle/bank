//currency.cpp
//currency transactions on the account
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "currency.hpp"

std::map<std::string, Currency> Currency::currencies_ =
  Currency::loadFromFile("data/currency.tsv");

Currency::Currency()
{
  entity_ = "UNKNOWN";
  currency_ = "N.A.";
  ncode_ = 0;
  minor_ = 0;
}

Currency::Currency(std::string line)
{
  std::stringstream ss(line);
  std::string value;
  std::getline(ss, entity_, '\t');
  std::getline(ss, currency_, '\t');
  std::getline(ss, acode_, '\t');

  ss >> ncode_;
  ss >> minor_;

  //std::getline(csv, value, '\t');
  //ncode_ = std::stoi(value);

  //std::getline(csv, value, '\t');
  //minor_ = std::stoi(value);
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

std::map<std::string, Currency> Currency::loadFromFile(std::string filename)
{
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    exit(1);
  }
  std::map<std::string, Currency> currencies;
  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    Currency c(line);
    if (c.acode_ == "SEK") {
      c.loadExchangeRates("data/exchange.tsv");
    }
    currencies[c.acode_] = c;
  }
  return currencies;
}

void Currency::loadExchangeRates(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }
    std::string line;
  while (std::getline(file, line)) {
    std::stringstream tsv(line);
    std::string value;
    double xRate;
    std::string targetCurr;

    std::getline(tsv, value, '\t');
    std::getline(tsv, targetCurr, '\t');
    std::getline(tsv, value, '\t');
    xRate = std::stod(value);

    exchangeRates[targetCurr] = xRate;
  }
  file.close();
}

int Currency::parse(std::string text)
{
  int amount = 0;
  bool negative = false;
  if (!text.empty() && text[0] == '-') {
    negative = true;
    text = text.substr(1);
  }

  if (!text.empty() && std::isdigit(text[0])) {
    size_t end;
    amount = std::stoi(text, &end, 10);
    amount *= pow10_[minor_];
    if (end < text.length()) {
      if (text[end] == '.') {
        text = text.substr(end + 1);
        int minor = std::stoi(text, &end, 10);
        amount += minor;
      }
    }
  }

  if (negative)
    amount = -amount;

  return amount;
}
