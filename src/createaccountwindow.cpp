#include "createaccountwindow.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <string>

CreateAccountWindow::CreateAccountWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Create New Account");

    layout->addWidget(new QLabel("Account Name:", this));
    nameInput = new QLineEdit(this);
    layout->addWidget(nameInput);

    QPushButton *createBtn = new QPushButton("Create", this);
    layout->addWidget(createBtn);

    connect(createBtn, &QPushButton::clicked, this, &CreateAccountWindow::onCreateClicked);

    resize(300, 150);
}

void CreateAccountWindow::onCreateClicked() {
    std::string name = nameInput->text().toStdString();
    if (name.empty()) {
        QMessageBox::warning(this, "Error", "Account name cannot be empty.");
        return;
    }

    // Determine next Account ID
    int maxAccountId = 2000;
    std::ifstream inFile("data/accounts.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            size_t pos = line.find(':');
            if (pos != std::string::npos) {
                try {
                    int id = std::stoi(line.substr(0, pos));
                    if (id > maxAccountId) maxAccountId = id;
                } catch (...) {}
            }
        }
        inFile.close();
    }

    int newId = maxAccountId + 1;
    std::ofstream outFile("data/accounts.txt", std::ios::app);
    if (outFile.is_open()) {
        // Format: id:userId:balance:currency:name
        outFile << newId << ":" << user_.getId() << ":0:0:" << name << "\n";
        outFile.close();

        Account newAccount(name, 0.0, user_.getId(), newId);
        emit accountCreated(newAccount);
        
        QMessageBox::information(this, "Success", "Account created successfully!");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not save account.");
    }
}