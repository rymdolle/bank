#ifndef TRANSFERWINDOW_HPP
#define TRANSFERWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "user.hpp"

class TransferWindow : public QWidget {
    Q_OBJECT

public:
    explicit TransferWindow(const User &user, QWidget *parent = nullptr);

signals:
    void transferSuccess(int srcId, int dstId, int amount);

private slots:
    void onTransferClicked();

private:
    User user_;
    QComboBox *sourceAccountCombo;
    QComboBox *destAccountCombo;
    QLineEdit *amountInput;
    QComboBox *categoryCombo;
};

#endif // TRANSFERWINDOW_HPP