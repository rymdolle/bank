#ifndef LOANWINDOW_HPP
#define LOANWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "user.hpp"

class LoanWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoanWindow(const User &user, QWidget *parent = nullptr);

signals:
    void loanApproved(int accountId, int amount);

private slots:
    void onRequestClicked();

private:
    User user_;
    QComboBox *accountCombo;
    QLineEdit *amountInput;
};

#endif // LOANWINDOW_HPP