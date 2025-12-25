#include "registerwindow.hpp"
#include "user.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <algorithm>

RegisterWindow::RegisterWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Register New User");

    layout->addWidget(new QLabel("Username:", this));
    usernameInput = new QLineEdit(this);
    layout->addWidget(usernameInput);

    layout->addWidget(new QLabel("Password:", this));
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordInput);

    layout->addWidget(new QLabel("Security Question:", this));
    questionInput = new QLineEdit(this);
    layout->addWidget(questionInput);

    layout->addWidget(new QLabel("Security Answer:", this));
    answerInput = new QLineEdit(this);
    layout->addWidget(answerInput);

    termsCheck = new QCheckBox("I agree to the Terms and Conditions", this);
    layout->addWidget(termsCheck);

    QPushButton *registerBtn = new QPushButton("Register", this);
    layout->addWidget(registerBtn);

    connect(registerBtn, &QPushButton::clicked, this, &RegisterWindow::onRegisterClicked);

    resize(300, 200);
}

void RegisterWindow::onRegisterClicked() {
    std::string username = usernameInput->text().toStdString();
    std::string password = passwordInput->text().toStdString();
    std::string question = questionInput->text().toStdString();
    std::string answer = answerInput->text().toStdString();

    if (username.empty() || password.empty() || question.empty() || answer.empty()) {
        QMessageBox::warning(this, "Error", "All fields are required.");
        return;
    }

    if (!termsCheck->isChecked()) {
        QMessageBox::warning(this, "Error", "You must agree to the Terms and Conditions.");
        return;
    }

    if (password.length() < 6) {
        QMessageBox::warning(this, "Error", "Password must be at least 6 characters long.");
        return;
    }

    std::vector<User> users = User::loadFromFile("data/users.txt");
    int maxId = 1000;
    for (const auto &user : users) {
        if (user.getName() == username) {
            QMessageBox::warning(this, "Error", "Username already exists.");
            return;
        }
        if (user.getId() > maxId) maxId = user.getId();
    }

    std::ofstream file("data/users.txt", std::ios::app);
    if (file.is_open()) {
        file << username << ":" << password << ":" << (maxId + 1) << "\n";
        file.close();

        std::ofstream secFile("data/security.txt", std::ios::app);
        if (secFile.is_open()) {
            secFile << username << ":" << question << ":" << answer << "\n";
            secFile.close();
        }

        // Create default "Savings" account
        int newUserId = maxId + 1;
        int maxAccountId = 2000;
        std::ifstream accIn("data/accounts.txt");
        if (accIn.is_open()) {
            std::string line;
            while (std::getline(accIn, line)) {
                if (line.empty()) continue;
                size_t pos = line.find(':');
                if (pos != std::string::npos) {
                    try {
                        int id = std::stoi(line.substr(0, pos));
                        if (id > maxAccountId) maxAccountId = id;
                    } catch (...) {}
                }
            }
            accIn.close();
        }
        std::ofstream accOut("data/accounts.txt", std::ios::app);
        if (accOut.is_open()) {
            // Format: id:userId:balance:currency:name
            accOut << (maxAccountId + 1) << ":" << newUserId << ":0:0:Savings\n";
            accOut.close();
        }

        QMessageBox::information(this, "Success", "User registered successfully! You can now login.");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not save user data.");
    }
}