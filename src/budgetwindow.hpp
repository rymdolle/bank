#ifndef BUDGETWINDOW_HPP
#define BUDGETWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include "user.hpp"

class BudgetWindow : public QWidget {
    Q_OBJECT
public:
    explicit BudgetWindow(const User &user, QWidget *parent = nullptr);

private slots:
    void onSaveClicked();
    void onAccountChanged();

private:
    User user_;
    QComboBox *accountCombo;
    QLineEdit *limitInput;
    void loadBudgetForCurrentAccount();
};

#endif // BUDGETWINDOW_HPP