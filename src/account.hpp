#ifndef ACCOUNT_MENU_HPP
#define ACCOUNT_MENU_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>


#include "transaction.hpp"

class Account
        {
private:
	std::string accountName_;
	double balance_;
	int userId_, id_;
	std::string currency_;
    static std::vector<Account> accounts_;

public:
	Account(std::string accountName, double balance, int userId, int id) {
		accountName_ = accountName;
		balance_ = balance;
		id_ = id;
		userId_ = userId;
          currency_ = "SEK";

	}
	std::string getAccountName() const {
		return accountName_;
	}

	double getBalance() const {
		return balance_;
	}

  std::string getCurrency() const {
    return currency_;
  }

	int getId() const {
		return id_;
	}
	int getUserId() const {
		return userId_;
	}
	void setBalance(double newBalance) {
		balance_ = newBalance;
	}



    double& getBalance() {
        return balance_;
    }
	static bool transferingMoney(int firstAccount, int secondAccount, int amount, int userId)
	{
		std::ifstream file("data/accounts.txt");
		std::ofstream tempFile("data/accounts_temp.txt");

		if (!file.is_open() || !tempFile.is_open())
		{
			std::cerr << "Could not open file for writing...\n";
			file.close();
			return false;
		}

		std::string line;
		bool accountFound = false;

		while (std::getline(file, line))
		{
			std::size_t pos = line.find(':');
			if (pos != std::string::npos)
			{
				int accountId = std::stoi(line.substr(5, pos - 5));
				double accountBalance = std::stod(line.substr(10, pos - 10));

				if (accountId == firstAccount || accountId == secondAccount)
				{
					if (accountId == firstAccount && accountBalance >= amount)
					{
						accountBalance -= amount;
					}
					else if (accountId == secondAccount)
					{
						accountBalance += amount;
					}
					else
					{
						std::cerr << "Not enough balance for account with ID: " << accountId << "\n";
						tempFile.close();
						file.close();
						return false;
					}
					std::size_t nameStart = line.find_first_not_of("0123456789.:");
					std::string accountName = line.substr(nameStart);

					Account updatedAccount(accountName, accountBalance, userId, accountId);

					tempFile << updatedAccount.getUserId() << ":" << updatedAccount.getId() << ":"
						<< updatedAccount.getBalance() << ":" << updatedAccount.getAccountName() << "\n";

					accountFound = true;
				}
				else
				{
					tempFile << line << "\n";
				}
			}
			else
			{
				tempFile << line << "\n";
			}
		}

		file.close();
		tempFile.close();

		if (!accountFound)
		{
			std::cerr << "Account with ID " << firstAccount << " or " << secondAccount << " not found.\n";
			return false;
		}

		std::remove("data/accounts.txt");
		std::rename("data/accounts_temp.txt", "data/accounts.txt");

		return true;
	}
	static bool handleMoney(int accountId, int amount, int userId, bool withdraw)
	{
		std::ifstream file("data/accounts.txt");
		std::ofstream tempFile("data/accounts_temp.txt");

		if (!file.is_open())
		{
			std::cerr << "Could not open file for reading...\n";
			return false;
		}

		if (!tempFile.is_open())
		{
			std::cerr << "Could not open file for writing...\n";
			file.close();
			return false;
		}

		std::string line;
		bool accountFound = false;

		while (std::getline(file, line))
		{
			std::size_t pos = line.find(':');
			if (pos != std::string::npos)
			{
				int account = std::stoi(line.substr(5, pos - 5));
				double accountBalance = std::stod(line.substr(pos + 1));

				if (account == accountId)
				{
					if (withdraw == true)
					{
						if (accountBalance < amount)
						{
							std::cerr << "Not enough balance for account with ID: " << accountId << "\n";
							tempFile.close();
							file.close();
							return false;
						}
						else
						{
							accountBalance -= amount;
						}
					}
					else
					{
						accountBalance += amount;
					}

					std::size_t nameStart = line.find_first_not_of("0123456789.:");
					std::string accountName = line.substr(nameStart);

					Account updatedAccount(accountName, accountBalance, userId, accountId);

					tempFile << std::to_string(updatedAccount.getId()) << ":" << std::to_string(updatedAccount.getBalance()) << ":"
						<< std::to_string(updatedAccount.getUserId()) << ":" << updatedAccount.getAccountName() << "\n";

					accountFound = true;
				}
				else
				{
					tempFile << line << "\n";
				}
			}
			else
			{
				tempFile << line << "\n";
			}
		}

		file.close();
		tempFile.close();

		if (!accountFound)
		{
			std::cerr << "Account with ID " << accountId << " not found.\n";
			return false;
		}

		std::remove("data/accounts.txt");
		std::rename("data/accounts_temp.txt", "data/accounts.txt");

		return true;
	}



    static std::vector<Account>& getAccounts()
    {
      return accounts_;
    }

  static std::vector<Account> loadFromFile(std::string filename)
  {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // Skip first line
    while (std::getline(file, line)) {
      if (line.empty())
        continue;
      std::stringstream ss(line);
      std::string name, currency;
      int64_t userId, accountId, balance;
      std::getline(ss, name, '\t');
      ss >> userId;
      ss >> accountId;
      ss >> balance;
      std::getline(ss, currency);
      accounts_.emplace_back(name, balance, userId, accountId);
    }
    return accounts_;
  }
};

#endif //ACCOUNT_MENU_HPP
