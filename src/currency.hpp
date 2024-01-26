#ifndef BANK_CURRENCY_HPP
#define BANK_CURRENCY_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <map>

class Currency
{
private:
  std::string entity_;
  std::string currency_;
  std::string acode_;
  int ncode_;
  int minor_;
  std::map<std::string, double> exchangeRates;

  static constexpr int pow10_[] = {1, 10, 100, 1000, 10'000, 100'000};
  static std::map<std::string, Currency> currencies_;

public:
  Currency();
  Currency(std::string line);
  ~Currency() = default;

  std::string format(int64_t amount);

  int parse(std::string text);
  static std::map<std::string, Currency>& get();
  static Currency& get(std::string acode);
  static void loadFromFile(std::string filename);
  void loadExchangeRates(std::string filename);

  double exchangeMonies(std::string acode, double amount) {
    return amount/exchangeRates[acode];
  }
};

#endif /* BANK_CURRENCY_HPP */
