#ifndef FORGOTPASSWORDWINDOW_HPP
#define FORGOTPASSWORDWINDOW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class ForgotPasswordWindow : public QWidget {
    Q_OBJECT
public:
    explicit ForgotPasswordWindow(QWidget *parent = nullptr);

private slots:
    void onSearchClicked();
    void onResetClicked();

private:
    QLineEdit *usernameInput;
    QLabel *questionLabel;
    QLineEdit *answerInput;
    QLineEdit *newPasswordInput;
    QPushButton *searchBtn;
    QPushButton *resetBtn;
    QWidget *resetContainer;
    
    std::string currentUsername;
    std::string currentAnswer;
};

#endif // FORGOTPASSWORDWINDOW_HPP