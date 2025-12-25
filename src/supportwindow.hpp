#ifndef SUPPORTWINDOW_HPP
#define SUPPORTWINDOW_HPP

#include <QWidget>
#include <QTextEdit>
#include "user.hpp"

class SupportWindow : public QWidget {
    Q_OBJECT
public:
    explicit SupportWindow(const User &user, QWidget *parent = nullptr);

private slots:
    void onSendClicked();

private:
    User user_;
    QTextEdit *messageInput;
};

#endif // SUPPORTWINDOW_HPP