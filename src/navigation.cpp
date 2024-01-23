#include "navigation.hpp"
#include "transaction.hpp" // Lägg till denna

Navigation::Navigation(User& loggedUser) :

	main_menu("Bank", MAIN),
	currentUser(loggedUser)
{
	Menu* menu;
	menu = new Menu("Account and balance", ACCOUNT);
	menu->addItem("Salary account");
	menu->addItem("Savings account");
	main_menu.addSubmenu(menu);

	menu = new Menu("Transfer", TRANSFER);
	menu->addItem("Transfer");
	menu->addItem("Withdraw");
	menu->addItem("Deposit");
	main_menu.addSubmenu(menu);

	menu = new Menu("Exchange", EXCHANGE);
	main_menu.addSubmenu(menu);
}


//
//void Navigation::showUserAccounts(const std::vector<Account>& accounts)
//{
//    // Grabs the corresponding userId to link to accId
//    int targetId = currentUser.getId();
//
//    // Prints out the accounts depending on what the currentUsers ID is
//    std::cout << "\tType:" << "\t\t\t\tAmount(Sek):\n";
//    for (const auto& Account : accVec)
//    {
//        if (Account.getId() == targetId)
//        {
//            std::cout << "\t" << Account.getType() << "\t\t\t" << Account.getBalance() << "\n";
//        }
//    }
//    std::cout << "\n";
//}

void Navigation::run()
{


	Transaction t;
	Menu* current = &main_menu;
	while (current != nullptr)
	{

		current->display();
		size_t choice, choice1;
		std::cin >> choice;
		std::cout << '\n';

		current = current->enter(choice);
		if (!current)
			break;
		switch (current->id)
		{
		case ACCOUNT:
			Account::getAccounts(currentUser.getId());
			break;
		case TRANSFER:
			std::cin >> choice1;
			if (choice1 == 1)
				t.transfer(currentUser);
			else if (choice == 2)
				t.withdraw(currentUser);
			else if (choice == 3)
				t.deposit(currentUser);
			//t.transferMenu(currentUser);
			break;
		case EXCHANGE:
		default:
			break;
		}
	}

}
