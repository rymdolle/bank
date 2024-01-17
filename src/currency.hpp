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

  static constexpr int pow10_[] = {1, 10, 100, 1000, 10'000, 100'000};
  static std::map<std::string, Currency> currencies_;

public:
  Currency();
  Currency(std::string line);
  ~Currency() = default;

  std::string format(int64_t amount);

  static Currency& get(std::string acode);
  static void loadFromFile(std::string filename);
};

#endif /* BANK_CURRENCY_HPP */
