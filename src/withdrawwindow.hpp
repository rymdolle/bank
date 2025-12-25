#ifndef WITHDRAWWINDOW_HPP
#define WITHDRAWWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "user.hpp"

class WithdrawWindow : public QWidget {
    Q_OBJECT

public:
    explicit WithdrawWindow(const User &user, QWidget *parent = nullptr);

signals:
    void withdrawSuccess(int accountId, int amount);

private slots:
    void onWithdrawClicked();

private:
    User user_;
    QComboBox *accountCombo;
    QLineEdit *amountInput;
    QComboBox *categoryCombo;
};

#endif // WITHDRAWWINDOW_HPP