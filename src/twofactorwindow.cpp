#include "twofactorwindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

TwoFactorWindow::TwoFactorWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Two-Factor Authentication");

    std::srand(std::time(nullptr));
    int code = 100000 + std::rand() % 900000;
    generatedCode = QString::number(code);

    layout->addWidget(new QLabel("A verification code has been sent to your device.", this));
    layout->addWidget(new QLabel("(Simulation: Your code is " + generatedCode + ")", this));

    layout->addWidget(new QLabel("Enter Code:", this));
    codeInput = new QLineEdit(this);
    layout->addWidget(codeInput);

    QPushButton *verifyBtn = new QPushButton("Verify", this);
    layout->addWidget(verifyBtn);
    connect(verifyBtn, &QPushButton::clicked, this, &TwoFactorWindow::onVerifyClicked);

    QPushButton *cancelBtn = new QPushButton("Cancel", this);
    layout->addWidget(cancelBtn);
    connect(cancelBtn, &QPushButton::clicked, this, &TwoFactorWindow::onCancelClicked);

    resize(300, 250);
}

void TwoFactorWindow::onVerifyClicked() {
    if (codeInput->text() == generatedCode) {
        emit verificationSuccessful();
        close();
    } else {
        QMessageBox::warning(this, "Error", "Invalid code.");
    }
}

void TwoFactorWindow::onCancelClicked() {
    emit canceled();
    close();
}