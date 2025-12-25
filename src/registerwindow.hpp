#ifndef REGISTERWINDOW_HPP
#define REGISTERWINDOW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

class RegisterWindow : public QWidget {
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);

private slots:
    void onRegisterClicked();

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QLineEdit *questionInput;
    QLineEdit *answerInput;
    QCheckBox *termsCheck;
};

#endif // REGISTERWINDOW_HPP