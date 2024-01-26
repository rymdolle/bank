#include "transaction.hpp"
#include "user.hpp"
#include "menu.hpp"

void Transaction::transfer(User& currentUser)
{
	int i = 0, firstChoice, secondChoice;
	double amount;
	std::vector<Account>& userAccounts = currentUser.getAccounts();

	std::cout << "From which account?\n";
	std::cin >> firstChoice;
	firstChoice -= 1;
	if (firstChoice < 0 || firstChoice > userAccounts.size())
	{
		std::cout << "Invalid account selecion.\n";
		return;
	}
	std::cout << "Too which account?\n";
	std::cin >> secondChoice;
	secondChoice -= 1;
	if (secondChoice < 0 || secondChoice> userAccounts.size() || secondChoice == firstChoice)
	{
		std::cout << "Invalid account selection.\n";
		return;
	}
	std::cout << "How much?\n";
	std::cin >> amount;

	if (amount <= 0 || amount > userAccounts[firstChoice].getBalance())
	{
		std::cout << "Invalid transfer amount.\n";
		return;
	}
	if (Account::transferingMoney(userAccounts[firstChoice].getId(), userAccounts[secondChoice].getId(), amount, currentUser.getId()))
		std::cout << "Transfer of " << amount << " from " << userAccounts[firstChoice].getAccountName()
		<< " to " << userAccounts[secondChoice].getAccountName() << " successful.\n";


}

void Transaction::withdraw(User& currentUser)
{
	int choice, amount;
	std::vector<Account>& userAccounts = currentUser.getAccounts();

	std::cout << "From which account?\n";
	std::cin >> choice;
	choice -= 1;
	if (choice < 0 || choice > userAccounts.size())
	{
		std::cout << "Invalid account selecion.\n";
		return;
	}
	std::cout << "How much?\n";
	std::cin >> amount;

	if (amount <= 0 || amount > userAccounts[choice].getBalance())
	{
		std::cout << "Invalid transfer amount.\n";
		return;
	}

	if (Account::handleMoney(userAccounts[choice].getId(), amount, currentUser.getId(), true))
		std::cout << "Withdraw of " << amount << " from " << userAccounts[choice].getAccountName()
		 << " successful.\n";
}

void Transaction::deposit(User& currentUser)
{
	int choice, amount;
	std::vector<Account>& userAccounts = currentUser.getAccounts();

	std::cout << "To which account?\n";
	std::cin >> choice;
	choice -= 1;
	if (choice < 0 || choice > userAccounts.size())
	{
		std::cout << "Invalid account selecion.\n";
		return;
	}
	std::cout << "How much?\n";
	std::cin >> amount;

	if (amount <= 0 || amount > userAccounts[choice].getBalance())
	{
		std::cout << "Invalid transfer amount.\n";
		return;
	}

	if (Account::handleMoney(userAccounts[choice].getId(), amount, currentUser.getId(), false))
		std::cout << "Deposit of " << amount << " from " << userAccounts[choice].getAccountName()
		<< " successful.\n";
}
