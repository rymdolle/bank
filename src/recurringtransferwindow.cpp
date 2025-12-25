#include "recurringtransferwindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDateTime>
#include <fstream>
#include "currency.hpp"

RecurringTransferWindow::RecurringTransferWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Schedule Recurring Transfer");

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

    layout->addWidget(new QLabel("Frequency:", this));
    frequencyCombo = new QComboBox(this);
    frequencyCombo->addItem("Daily", 1);
    frequencyCombo->addItem("Weekly", 7);
    frequencyCombo->addItem("Monthly", 30);
    layout->addWidget(frequencyCombo);

    layout->addWidget(new QLabel("Number of Executions:", this));
    occurrencesSpin = new QSpinBox(this);
    occurrencesSpin->setRange(1, 100);
    layout->addWidget(occurrencesSpin);

    QPushButton *scheduleBtn = new QPushButton("Schedule", this);
    layout->addWidget(scheduleBtn);
    connect(scheduleBtn, &QPushButton::clicked, this, &RecurringTransferWindow::onScheduleClicked);

    resize(300, 400);
}

void RecurringTransferWindow::onScheduleClicked() {
    int srcIndex = sourceAccountCombo->currentIndex();
    int dstIndex = destAccountCombo->currentIndex();
    if (srcIndex < 0 || dstIndex < 0) return;

    int srcId = sourceAccountCombo->currentData().toInt();
    int dstId = destAccountCombo->currentData().toInt();

    if (srcId == dstId) {
        QMessageBox::warning(this, "Error", "Cannot transfer to same account.");
        return;
    }

    std::string amountStr = amountInput->text().toStdString();
    std::string currency = user_.getAccounts()[srcIndex].getCurrency();
    int amount = Currency::get(currency).parse(amountStr);

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Invalid amount.");
        return;
    }

    int intervalDays = frequencyCombo->currentData().toInt();
    int count = occurrencesSpin->value();
    QDateTime nextRun = QDateTime::currentDateTime().addDays(intervalDays);
    
    std::ofstream file("data/recurring_transfers.txt", std::ios::app);
    if (file.is_open()) {
        file << user_.getId() << ":" << srcId << ":" << dstId << ":" << amount << ":" << intervalDays << ":" << nextRun.toSecsSinceEpoch() << ":" << count << "\n";
        file.close();
        QMessageBox::information(this, "Success", "Transfer scheduled!");
        emit transferScheduled();
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not save schedule.");
    }
}