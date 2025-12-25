#ifndef DEPOSITWINDOW_HPP
#define DEPOSITWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "user.hpp"

class DepositWindow : public QWidget {
    Q_OBJECT

public:
    explicit DepositWindow(const User &user, QWidget *parent = nullptr);

signals:
    void depositSuccess(int accountId, int amount);

private slots:
    void onDepositClicked();

private:
    User user_;
    QComboBox *accountCombo;
    QLineEdit *amountInput;
    QComboBox *categoryCombo;
};

#endif // DEPOSITWINDOW_HPP