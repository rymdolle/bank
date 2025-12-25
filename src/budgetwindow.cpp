#include "budgetwindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

BudgetWindow::BudgetWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Set Account Budget");

    layout->addWidget(new QLabel("Select Account:", this));
    accountCombo = new QComboBox(this);
    for (const auto &acc : user_.getAccounts()) {
        accountCombo->addItem(QString::fromStdString(acc.getAccountName()), QVariant(acc.getId()));
    }
    connect(accountCombo, &QComboBox::currentIndexChanged, this, &BudgetWindow::onAccountChanged);
    layout->addWidget(accountCombo);

    layout->addWidget(new QLabel("Monthly Spending Limit:", this));
    limitInput = new QLineEdit(this);
    layout->addWidget(limitInput);

    QPushButton *saveBtn = new QPushButton("Save Budget", this);
    layout->addWidget(saveBtn);
    connect(saveBtn, &QPushButton::clicked, this, &BudgetWindow::onSaveClicked);

    resize(300, 200);
    loadBudgetForCurrentAccount();
}

void BudgetWindow::onAccountChanged() {
    loadBudgetForCurrentAccount();
}

void BudgetWindow::loadBudgetForCurrentAccount() {
    if (accountCombo->currentIndex() < 0) return;
    int accountId = accountCombo->currentData().toInt();
    
    std::ifstream file("data/budgets.txt");
    std::string line;
    bool found = false;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while(std::getline(ss, segment, ':')) parts.push_back(segment);
            
            if (parts.size() >= 2) {
                if (std::stoi(parts[0]) == accountId) {
                    limitInput->setText(QString::fromStdString(parts[1]));
                    found = true;
                    break;
                }
            }
        }
        file.close();
    }
    if (!found) limitInput->clear();
}

void BudgetWindow::onSaveClicked() {
    if (accountCombo->currentIndex() < 0) return;
    int accountId = accountCombo->currentData().toInt();
    std::string limitStr = limitInput->text().toStdString();
    
    if (limitStr.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a limit.");
        return;
    }

    // Update file
    std::ifstream inFile("data/budgets.txt");
    std::vector<std::string> lines;
    std::string line;
    
    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string idStr;
            std::getline(ss, idStr, ':');
            if (!idStr.empty()) {
                try {
                    if (std::stoi(idStr) != accountId) {
                        lines.push_back(line);
                    }
                } catch(...) {}
            }
        }
        inFile.close();
    }

    std::ofstream outFile("data/budgets.txt");
    for (const auto &l : lines) outFile << l << "\n";
    outFile << accountId << ":" << limitStr << "\n";
    outFile.close();

    QMessageBox::information(this, "Success", "Budget set successfully!");
    close();
}