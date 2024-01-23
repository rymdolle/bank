#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <vector>
#include <string>
class User;

class Transaction
{
public:
	void transfer(const User& currentUser);
	void withdraw(const User& currentUser);
	void deposit(const User& currentUser);

};

#endif /* TRANSACTION_H */
