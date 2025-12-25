#ifndef INTERESTWINDOW_HPP
#define INTERESTWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "user.hpp"

class InterestWindow : public QWidget {
    Q_OBJECT

public:
    explicit InterestWindow(const User &user, QWidget *parent = nullptr);

signals:
    void interestApplied(int accountId, int amount);

private slots:
    void onApplyClicked();

private:
    User user_;
    QComboBox *accountCombo;
    double interestRate = 0.05; // 5% interest rate
};

#endif // INTERESTWINDOW_HPP