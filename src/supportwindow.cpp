#include "supportwindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDateTime>
#include <fstream>

SupportWindow::SupportWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Contact Support");

    layout->addWidget(new QLabel("Describe your issue:", this));
    messageInput = new QTextEdit(this);
    layout->addWidget(messageInput);

    QPushButton *sendBtn = new QPushButton("Send Message", this);
    layout->addWidget(sendBtn);
    connect(sendBtn, &QPushButton::clicked, this, &SupportWindow::onSendClicked);

    resize(400, 300);
}

void SupportWindow::onSendClicked() {
    QString message = messageInput->toPlainText().trimmed();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Error", "Message cannot be empty.");
        return;
    }

    std::ofstream file("data/support_messages.txt", std::ios::app);
    if (file.is_open()) {
        file << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << "] "
             << "User ID " << user_.getId() << ": " << message.toStdString() << "\n"
             << "--------------------------------------------------\n";
        file.close();
        QMessageBox::information(this, "Success", "Message sent to support!");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Could not send message.");
    }
}