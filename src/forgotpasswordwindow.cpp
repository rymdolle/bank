#include "forgotpasswordwindow.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

ForgotPasswordWindow::ForgotPasswordWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Forgot Password");

    layout->addWidget(new QLabel("Enter your username:", this));
    usernameInput = new QLineEdit(this);
    layout->addWidget(usernameInput);

    searchBtn = new QPushButton("Search", this);
    layout->addWidget(searchBtn);
    connect(searchBtn, &QPushButton::clicked, this, &ForgotPasswordWindow::onSearchClicked);

    resetContainer = new QWidget(this);
    QVBoxLayout *resetLayout = new QVBoxLayout(resetContainer);
    
    resetLayout->addWidget(new QLabel("Security Question:", resetContainer));
    questionLabel = new QLabel("", resetContainer);
    resetLayout->addWidget(questionLabel);

    resetLayout->addWidget(new QLabel("Answer:", resetContainer));
    answerInput = new QLineEdit(resetContainer);
    resetLayout->addWidget(answerInput);

    resetLayout->addWidget(new QLabel("New Password:", resetContainer));
    newPasswordInput = new QLineEdit(resetContainer);
    newPasswordInput->setEchoMode(QLineEdit::Password);
    resetLayout->addWidget(newPasswordInput);

    resetBtn = new QPushButton("Reset Password", resetContainer);
    resetLayout->addWidget(resetBtn);
    connect(resetBtn, &QPushButton::clicked, this, &ForgotPasswordWindow::onResetClicked);

    layout->addWidget(resetContainer);
    resetContainer->hide();

    resize(300, 300);
}

void ForgotPasswordWindow::onSearchClicked() {
    std::string username = usernameInput->text().toStdString();
    if (username.empty()) return;

    std::ifstream file("data/security.txt");
    std::string line;
    bool found = false;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string u, q, a;
            std::getline(ss, u, ':');
            std::getline(ss, q, ':');
            std::getline(ss, a, ':');

            if (u == username) {
                currentUsername = u;
                questionLabel->setText(QString::fromStdString(q));
                currentAnswer = a;
                found = true;
                break;
            }
        }
        file.close();
    }

    if (found) {
        resetContainer->show();
        searchBtn->setDisabled(true);
        usernameInput->setDisabled(true);
    } else {
        QMessageBox::warning(this, "Error", "User not found or no security question set.");
    }
}

void ForgotPasswordWindow::onResetClicked() {
    std::string answer = answerInput->text().toStdString();
    std::string newPass = newPasswordInput->text().toStdString();

    if (answer != currentAnswer) {
        QMessageBox::warning(this, "Error", "Incorrect answer.");
        return;
    }

    if (newPass.length() < 6) {
        QMessageBox::warning(this, "Error", "Password must be at least 6 characters.");
        return;
    }

    // Update users.txt
    std::ifstream inFile("data/users.txt");
    std::vector<std::string> lines;
    std::string line;
    bool updated = false;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while(std::getline(ss, segment, ':')) parts.push_back(segment);

            if (parts.size() >= 3) {
                if (parts[0] == currentUsername) {
                    // username:password:id
                    line = parts[0] + ":" + newPass + ":" + parts[2];
                    updated = true;
                }
            }
            lines.push_back(line);
        }
        inFile.close();
    }

    if (updated) {
        std::ofstream outFile("data/users.txt");
        for (const auto &l : lines) outFile << l << "\n";
        outFile.close();
        QMessageBox::information(this, "Success", "Password reset successfully.");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not update password.");
    }
}