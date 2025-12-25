#include "loanwindow.hpp"
#include <QDateTime>
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <vector>
#include "currency.hpp"

LoanWindow::LoanWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Request Loan");

    layout->addWidget(new QLabel("Select Account to Deposit Loan:", this));
    accountCombo = new QComboBox(this);
    for (const auto &acc : user_.getAccounts()) {
        accountCombo->addItem(QString::fromStdString(acc.getAccountName()), QVariant(acc.getId()));
    }
    layout->addWidget(accountCombo);

    layout->addWidget(new QLabel("Loan Amount:", this));
    amountInput = new QLineEdit(this);
    layout->addWidget(amountInput);

    QPushButton *requestBtn = new QPushButton("Request Loan", this);
    layout->addWidget(requestBtn);

    connect(requestBtn, &QPushButton::clicked, this, &LoanWindow::onRequestClicked);

    resize(300, 200);
}

void LoanWindow::onRequestClicked() {
    int index = accountCombo->currentIndex();
    if (index < 0) return;

    int accountId = accountCombo->currentData().toInt();
    std::string amountStr = amountInput->text().toStdString();
    
    auto& accounts = user_.getAccounts();
    std::string currencyType = accounts[index].getCurrency();
    int amount = Currency::get(currencyType).parse(amountStr);

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Invalid loan amount.");
        return;
    }

    // Simple credit check: Max loan limit (e.g., 100,000 units)
    if (amount > 100000) {
        QMessageBox::warning(this, "Loan Denied", "Loan amount exceeds the maximum limit of 100,000.");
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

            if (parts.size() >= 3) {
                try {
                    int id = std::stoi(parts[0]);
                    if (id == accountId) {
                        double currentBalance = std::stod(parts[2]);
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
            logFile << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << "] Loan Approved " << Currency::get(currencyType).format(amount)
                    << " to Account " << accountId << "\n";
        }

        if (amount >= 10000) {
             std::ofstream noteFile("data/notifications.txt", std::ios::app);
             if (noteFile.is_open()) {
                 noteFile << user_.getId() << ":Large Loan of " << Currency::get(currencyType).format(amount) << " approved.\n";
             }
        }

        emit loanApproved(accountId, amount);
        QMessageBox::information(this, "Success", "Loan approved and funds deposited!");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not update account database.");
    }
}