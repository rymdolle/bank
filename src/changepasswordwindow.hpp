#ifndef CHANGEPASSWORDWINDOW_HPP
#define CHANGEPASSWORDWINDOW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "user.hpp"

class ChangePasswordWindow : public QWidget {
    Q_OBJECT

public:
    explicit ChangePasswordWindow(const User &user, QWidget *parent = nullptr);

private slots:
    void onChangeClicked();

private:
    User user_;
    QLineEdit *oldPasswordInput;
    QLineEdit *newPasswordInput;
    QLineEdit *confirmPasswordInput;
};

#endif // CHANGEPASSWORDWINDOW_HPP