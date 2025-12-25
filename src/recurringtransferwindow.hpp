#ifndef RECURRINGTRANSFERWINDOW_HPP
#define RECURRINGTRANSFERWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include "user.hpp"

class RecurringTransferWindow : public QWidget {
    Q_OBJECT
public:
    explicit RecurringTransferWindow(const User &user, QWidget *parent = nullptr);

signals:
    void transferScheduled();

private slots:
    void onScheduleClicked();

private:
    User user_;
    QComboBox *sourceAccountCombo;
    QComboBox *destAccountCombo;
    QLineEdit *amountInput;
    QComboBox *frequencyCombo;
    QSpinBox *occurrencesSpin;
};

#endif // RECURRINGTRANSFERWINDOW_HPP