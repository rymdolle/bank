#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include "dashboardwindow.hpp"
class RegisterWindow;
class TwoFactorWindow;
class ForgotPasswordWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onTwoFactorSuccess();
    void onForgotPasswordClicked();

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QLabel *statusLabel;
    DashboardWindow *dashboardWindow = nullptr;
    RegisterWindow *registerWindow = nullptr;
    TwoFactorWindow *twoFactorWindow = nullptr;
    ForgotPasswordWindow *forgotPasswordWindow = nullptr;
    User pendingUser;
};

#endif // MAINWINDOW_HPP