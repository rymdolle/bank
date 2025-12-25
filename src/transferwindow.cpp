#include "transferwindow.hpp"
#include <QDateTime>
#include <fstream>
#include <QVBoxLayout>
#include <QMessageBox>
#include "account.hpp"
#include "currency.hpp"

TransferWindow::TransferWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Transfer Money");

    layout->addWidget(new QLabel("From Account:", this));
    sourceAccountCombo = new QComboBox(this);
    for (const auto &acc : user_.getAccounts()) {
        sourceAccountCombo->addItem(QString::fromStdString(acc.getAccountName()), QVariant(acc.getId()));
    }
    layout->addWidget(sourceAccountCombo);

    layout->addWidget(new QLabel("To Account:", this));
    destAccountCombo = new QComboBox(this);
    for (const auto &acc : user_.getAccounts()) {
        destAccountCombo->addItem(QString::fromStdString(acc.getAccountName()), QVariant(acc.getId()));
    }
    layout->addWidget(destAccountCombo);

    layout->addWidget(new QLabel("Amount:", this));
    amountInput = new QLineEdit(this);
    layout->addWidget(amountInput);

    layout->addWidget(new QLabel("Category:", this));
    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"General", "Food", "Rent", "Utilities", "Entertainment", "Other"});
    layout->addWidget(categoryCombo);

    QPushButton *transferBtn = new QPushButton("Transfer", this);
    layout->addWidget(transferBtn);

    connect(transferBtn, &QPushButton::clicked, this, &TransferWindow::onTransferClicked);

    resize(300, 300);
}

void TransferWindow::onTransferClicked() {
    int srcIndex = sourceAccountCombo->currentIndex();
    int dstIndex = destAccountCombo->currentIndex();

    if (srcIndex < 0 || dstIndex < 0) return;

    int srcId = sourceAccountCombo->currentData().toInt();
    int dstId = destAccountCombo->currentData().toInt();

    if (srcId == dstId) {
        QMessageBox::warning(this, "Error", "Cannot transfer to the same account.");
        return;
    }

    Account srcAccount = user_.getAccounts()[srcIndex];
    std::string amountStr = amountInput->text().toStdString();
    int amount = Currency::get(srcAccount.getCurrency()).parse(amountStr);

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Invalid amount.");
        return;
    }

    if (amount > srcAccount.getBalance()) {
        QMessageBox::warning(this, "Error", "Insufficient funds.");
        return;
    }

    if (Account::transferingMoney(srcId, dstId, amount, user_.getId())) {
        QMessageBox::information(this, "Success", "Transfer successful!");

        std::ofstream logFile("data/transactions.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << "] [" << categoryCombo->currentText().toStdString() << "] Transferred " << Currency::get(srcAccount.getCurrency()).format(amount)
                    << " from Account " << srcId << " to Account " << dstId << "\n";
        }

        if (amount >= 10000) {
             std::ofstream noteFile("data/notifications.txt", std::ios::app);
             if (noteFile.is_open()) {
                 noteFile << user_.getId() << ":Large Transfer of " << Currency::get(srcAccount.getCurrency()).format(amount) << " performed.\n";
             }
        }

        emit transferSuccess(srcId, dstId, amount);
        close();
    } else {
        QMessageBox::critical(this, "Error", "Transfer failed.");
    }
}