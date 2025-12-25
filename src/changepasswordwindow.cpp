#include "changepasswordwindow.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

ChangePasswordWindow::ChangePasswordWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Change Password");

    layout->addWidget(new QLabel("Old Password:", this));
    oldPasswordInput = new QLineEdit(this);
    oldPasswordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(oldPasswordInput);

    layout->addWidget(new QLabel("New Password:", this));
    newPasswordInput = new QLineEdit(this);
    newPasswordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(newPasswordInput);

    layout->addWidget(new QLabel("Confirm New Password:", this));
    confirmPasswordInput = new QLineEdit(this);
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(confirmPasswordInput);

    QPushButton *changeBtn = new QPushButton("Change Password", this);
    layout->addWidget(changeBtn);

    connect(changeBtn, &QPushButton::clicked, this, &ChangePasswordWindow::onChangeClicked);

    resize(300, 250);
}

void ChangePasswordWindow::onChangeClicked() {
    std::string oldPass = oldPasswordInput->text().toStdString();
    std::string newPass = newPasswordInput->text().toStdString();
    std::string confirmPass = confirmPasswordInput->text().toStdString();

    if (oldPass.empty() || newPass.empty()) {
        QMessageBox::warning(this, "Error", "Fields cannot be empty.");
        return;
    }

    if (!user_.verify(user_.getName(), oldPass)) {
         QMessageBox::warning(this, "Error", "Incorrect old password.");
         return;
    }

    if (newPass.length() < 6) {
        QMessageBox::warning(this, "Error", "New password must be at least 6 characters.");
        return;
    }

    if (newPass != confirmPass) {
        QMessageBox::warning(this, "Error", "New passwords do not match.");
        return;
    }

    // Update file
    std::ifstream inFile("data/users.txt");
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while(std::getline(ss, segment, ':')) parts.push_back(segment);

            if (parts.size() >= 3) {
                try {
                    int id = std::stoi(parts[2]);
                    if (id == user_.getId()) {
                        // Reconstruct line with new password: username:password:id
                        line = parts[0] + ":" + newPass + ":" + parts[2];
                        found = true;
                    }
                } catch (...) {}
            }
            lines.push_back(line);
        }
        inFile.close();
    }

    if (found) {
        std::ofstream outFile("data/users.txt");
        for (const auto &l : lines) {
            outFile << l << "\n";
        }
        outFile.close();
        QMessageBox::information(this, "Success", "Password changed successfully.");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not update password database.");
    }
}