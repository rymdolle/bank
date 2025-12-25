#include "interestwindow.hpp"
#include <QDateTime>
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "currency.hpp"

InterestWindow::InterestWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Calculate Interest");

    layout->addWidget(new QLabel("Select Account:", this));
    accountCombo = new QComboBox(this);
    for (const auto &acc : user_.getAccounts()) {
        accountCombo->addItem(QString::fromStdString(acc.getAccountName()), QVariant(acc.getId()));
    }
    layout->addWidget(accountCombo);

    layout->addWidget(new QLabel("Interest Rate: 5%", this));

    QPushButton *applyBtn = new QPushButton("Apply Interest", this);
    layout->addWidget(applyBtn);

    connect(applyBtn, &QPushButton::clicked, this, &InterestWindow::onApplyClicked);

    resize(300, 150);
}

void InterestWindow::onApplyClicked() {
    int index = accountCombo->currentIndex();
    if (index < 0) return;

    int accountId = accountCombo->currentData().toInt();
    auto& accounts = user_.getAccounts();
    std::string currencyType = accounts[index].getCurrency();

    // Update file
    std::ifstream inFile("data/accounts.txt");
    std::vector<std::string> lines;
    std::string line;
    bool found = false;
    int interestAmount = 0;

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
                        interestAmount = static_cast<int>(currentBalance * interestRate);
                        
                        std::string newLine = parts[0] + ":" + parts[1] + ":" + std::to_string((int)(currentBalance + interestAmount));
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

    if (found && interestAmount > 0) {
        std::ofstream outFile("data/accounts.txt");
        for (const auto &l : lines) outFile << l << "\n";
        outFile.close();

        std::ofstream logFile("data/transactions.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << "] Interest Applied " << Currency::get(currencyType).format(interestAmount)
                    << " to Account " << accountId << "\n";
        }

        if (interestAmount >= 10000) {
             std::ofstream noteFile("data/notifications.txt", std::ios::app);
             if (noteFile.is_open()) {
                 noteFile << user_.getId() << ":Large Interest of " << Currency::get(currencyType).format(interestAmount) << " applied.\n";
             }
        }

        emit interestApplied(accountId, interestAmount);
        QMessageBox::information(this, "Success", "Interest applied successfully!");
        close();
    } else {
        QMessageBox::information(this, "Info", "Could not apply interest (balance too low or account not found).");
    }
}