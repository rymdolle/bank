#include "withdrawwindow.hpp"
#include <QDateTime>
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <vector>
#include "currency.hpp"

WithdrawWindow::WithdrawWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Withdraw Funds");

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
    categoryCombo->addItems({"Food", "Entertainment", "Utilities", "Rent", "Shopping", "Other"});
    layout->addWidget(categoryCombo);

    QPushButton *withdrawBtn = new QPushButton("Withdraw", this);
    layout->addWidget(withdrawBtn);

    connect(withdrawBtn, &QPushButton::clicked, this, &WithdrawWindow::onWithdrawClicked);

    resize(300, 200);
}

void WithdrawWindow::onWithdrawClicked() {
    int index = accountCombo->currentIndex();
    if (index < 0) return;

    int accountId = accountCombo->currentData().toInt();
    std::string amountStr = amountInput->text().toStdString();
    
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
    bool sufficientFunds = true;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while(std::getline(ss, segment, ':')) parts.push_back(segment);

            if (parts.size() >= 3) {
                try {
                    int id = std::stoi(parts[0]);
                    if (id == accountId) {
                        double currentBalance = std::stod(parts[2]);
                        if (amount > currentBalance) {
                            sufficientFunds = false;
                        } else {
                            std::string newLine = parts[0] + ":" + parts[1] + ":" + std::to_string((int)(currentBalance - amount));
                            for(size_t i = 3; i < parts.size(); ++i) newLine += ":" + parts[i];
                            lines.push_back(newLine);
                            found = true;
                        }
                        if (!sufficientFunds) lines.push_back(line);
                        continue;
                    }
                } catch (...) {}
            }
            lines.push_back(line);
        }
        inFile.close();
    }

    if (!sufficientFunds) {
        QMessageBox::warning(this, "Error", "Insufficient funds.");
    } else if (found) {
        std::ofstream outFile("data/accounts.txt");
        for (const auto &l : lines) outFile << l << "\n";
        outFile.close();

        // Log transaction
        std::ofstream logFile("data/transactions.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << "] [" << categoryCombo->currentText().toStdString() << "] Withdrew " << Currency::get(currencyType).format(amount)
                    << " from Account " << accountId << "\n";
        }

        if (amount >= 10000) {
             std::ofstream noteFile("data/notifications.txt", std::ios::app);
             if (noteFile.is_open()) {
                 noteFile << user_.getId() << ":Large Withdrawal of " << Currency::get(currencyType).format(amount) << " performed.\n";
             }
        }

        emit withdrawSuccess(accountId, amount);
        QMessageBox::information(this, "Success", "Withdrawal successful!");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not update account database.");
    }
}