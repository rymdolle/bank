#include "depositwindow.hpp"
#include <QDateTime>
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <vector>
#include "currency.hpp"

DepositWindow::DepositWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Deposit Funds");

    layout->addWidget(new QLabel("Select Account:", this));
    accountCombo = new QComboBox(this);
    for (const auto &acc : user_.getAccounts()) {
        accountCombo->addItem(QString::fromStdString(acc.getAccountName()), QVariant(acc.getId()));
    }
    layout->addWidget(accountCombo);

    layout->addWidget(new QLabel("Amount:", this));
    amountInput = new QLineEdit(this);
    layout->addWidget(amountInput);

    layout->addWidget(new QLabel("Category:", this));
    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"Salary", "Gift", "Refund", "Other"});
    layout->addWidget(categoryCombo);

    QPushButton *depositBtn = new QPushButton("Deposit", this);
    layout->addWidget(depositBtn);

    connect(depositBtn, &QPushButton::clicked, this, &DepositWindow::onDepositClicked);

    resize(300, 200);
}

void DepositWindow::onDepositClicked() {
    int index = accountCombo->currentIndex();
    if (index < 0) return;

    int accountId = accountCombo->currentData().toInt();
    std::string amountStr = amountInput->text().toStdString();
    
    // Use the account's currency to parse the input
    auto& accounts = user_.getAccounts();
    std::string currencyType = accounts[index].getCurrency();
    int amount = Currency::get(currencyType).parse(amountStr);

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Invalid amount.");
        return;
    }

    // Update file
    std::ifstream inFile("data/accounts.txt");
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while(std::getline(ss, segment, ':')) parts.push_back(segment);

            // Format: id:userId:balance:currency:name
            if (parts.size() >= 3) {
                try {
                    int id = std::stoi(parts[0]);
                    if (id == accountId) {
                        double currentBalance = std::stod(parts[2]);
                        // Reconstruct line with new balance
                        std::string newLine = parts[0] + ":" + parts[1] + ":" + std::to_string((int)(currentBalance + amount));
                        for(size_t i = 3; i < parts.size(); ++i) newLine += ":" + parts[i];
                        lines.push_back(newLine);
                        found = true;
                        continue;
                    }
                } catch (...) {}
            }
            lines.push_back(line);
        }
        inFile.close();
    }

    if (found) {
        std::ofstream outFile("data/accounts.txt");
        for (const auto &l : lines) outFile << l << "\n";
        outFile.close();

        // Log transaction
        std::ofstream logFile("data/transactions.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << "] [" << categoryCombo->currentText().toStdString() << "] Deposited " << Currency::get(currencyType).format(amount)
                    << " to Account " << accountId << "\n";
        }

        if (amount >= 10000) {
             std::ofstream noteFile("data/notifications.txt", std::ios::app);
             if (noteFile.is_open()) {
                 noteFile << user_.getId() << ":Large Deposit of " << Currency::get(currencyType).format(amount) << " performed.\n";
             }
        }

        emit depositSuccess(accountId, amount);
        QMessageBox::information(this, "Success", "Deposit successful!");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not update account database.");
    }
}