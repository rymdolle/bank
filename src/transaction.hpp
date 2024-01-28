//transaction.hpp
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <vector>
#include <string>
class User;

class Transaction
{
public:
	void transfer(User& currentUser);//transaction
	void withdraw(User& currentUser);// fail
	void deposit(User& currentUser);//transaction on the deposit's account

};

#endif /* TRANSACTION_H */
