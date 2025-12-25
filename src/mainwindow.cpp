#include "mainwindow.hpp"
#include <QMessageBox>
#include "user.hpp"
#include "registerwindow.hpp"
#include "twofactorwindow.hpp"
#include "forgotpasswordwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Title
    QLabel *titleLabel = new QLabel("Bank System", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont font = titleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    titleLabel->setFont(font);
    layout->addWidget(titleLabel);

    // Username
    layout->addWidget(new QLabel("Username:", this));
    usernameInput = new QLineEdit(this);
    layout->addWidget(usernameInput);

    // Password
    layout->addWidget(new QLabel("Password:", this));
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordInput);

    // Login Button
    QPushButton *loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    QPushButton *registerButton = new QPushButton("Register", this);
    layout->addWidget(registerButton);
    connect(registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterClicked);

    QPushButton *forgotBtn = new QPushButton("Forgot Password?", this);
    layout->addWidget(forgotBtn);
    connect(forgotBtn, &QPushButton::clicked, this, &MainWindow::onForgotPasswordClicked);

    // Status Label
    statusLabel = new QLabel(this);
    statusLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(statusLabel);

    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    resize(300, 250);
}

MainWindow::~MainWindow() {
    if (dashboardWindow) {
        delete dashboardWindow;
    }
    if (registerWindow) {
        delete registerWindow;
    }
    if (twoFactorWindow) {
        delete twoFactorWindow;
    }
    if (forgotPasswordWindow) {
        delete forgotPasswordWindow;
    }
}

void MainWindow::onRegisterClicked() {
    if (registerWindow) delete registerWindow;
    registerWindow = new RegisterWindow();
    registerWindow->show();
}

void MainWindow::onLoginClicked() {
    QString qUsername = usernameInput->text();
    QString qPassword = passwordInput->text();

    // Convert to std::string for compatibility with User class
    std::string username = qUsername.toStdString();
    std::string password = qPassword.toStdString();

    // Load users and attempt to verify
    std::vector<User> users = User::loadFromFile("data/users.txt");
    bool success = false;

    for (User &user : users) {
        if (user.verify(username, password)) {
            statusLabel->setText("Credentials verified. Enter 2FA code.");
            pendingUser = user;
            
            if (twoFactorWindow) delete twoFactorWindow;
            twoFactorWindow = new TwoFactorWindow();
            connect(twoFactorWindow, &TwoFactorWindow::verificationSuccessful, this, &MainWindow::onTwoFactorSuccess);
            connect(twoFactorWindow, &TwoFactorWindow::canceled, this, &MainWindow::show);
            twoFactorWindow->show();
            
            this->hide();
            success = true;
            break;
        }
    }

    if (!success) {
        statusLabel->setText("Login failed.");
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::onTwoFactorSuccess() {
    if (dashboardWindow) delete dashboardWindow;
    dashboardWindow = new DashboardWindow(pendingUser);
    connect(dashboardWindow, &DashboardWindow::logout, this, &MainWindow::show);
    dashboardWindow->show();
}

void MainWindow::onForgotPasswordClicked() {
    if (forgotPasswordWindow) delete forgotPasswordWindow;
    forgotPasswordWindow = new ForgotPasswordWindow();
    forgotPasswordWindow->show();
}