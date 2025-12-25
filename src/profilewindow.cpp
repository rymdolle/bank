#include "profilewindow.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

ProfileWindow::ProfileWindow(User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("User Profile");

    layout->addWidget(new QLabel("User ID (Cannot be changed):", this));
    idLabel = new QLabel(QString::number(user_.getId()), this);
    layout->addWidget(idLabel);

    layout->addWidget(new QLabel("Username:", this));
    nameInput = new QLineEdit(QString::fromStdString(user_.getName()), this);
    layout->addWidget(nameInput);

    QPushButton *saveBtn = new QPushButton("Save Changes", this);
    layout->addWidget(saveBtn);

    connect(saveBtn, &QPushButton::clicked, this, &ProfileWindow::onSaveClicked);

    resize(300, 200);
}

void ProfileWindow::onSaveClicked() {
    std::string newName = nameInput->text().toStdString();
    if (newName.empty()) {
        QMessageBox::warning(this, "Error", "Username cannot be empty.");
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
                        // Reconstruct line: newName:password:id
                        line = newName + ":" + parts[1] + ":" + parts[2];
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
        for (const auto &l : lines) outFile << l << "\n";
        outFile.close();

        user_.setName(newName);
        emit nameChanged(newName);
        QMessageBox::information(this, "Success", "Profile updated successfully.");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not update profile.");
    }
}