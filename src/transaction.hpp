#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <vector>
#include <string>
class User;

class Transaction
{
public:
	void transfer(User& currentUser);
	void withdraw(User& currentUser);
	void deposit(User& currentUser);

};

#endif /* TRANSACTION_H */
