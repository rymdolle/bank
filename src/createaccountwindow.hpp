#ifndef CREATEACCOUNTWINDOW_HPP
#define CREATEACCOUNTWINDOW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "user.hpp"
#include "account.hpp"

class CreateAccountWindow : public QWidget {
    Q_OBJECT

public:
    explicit CreateAccountWindow(const User &user, QWidget *parent = nullptr);

signals:
    void accountCreated(const Account &account);

private slots:
    void onCreateClicked();

private:
    User user_;
    QLineEdit *nameInput;
};

#endif // CREATEACCOUNTWINDOW_HPP