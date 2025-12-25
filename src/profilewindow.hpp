#ifndef PROFILEWINDOW_HPP
#define PROFILEWINDOW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "user.hpp"

class ProfileWindow : public QWidget {
    Q_OBJECT

public:
    explicit ProfileWindow(User &user, QWidget *parent = nullptr);

signals:
    void nameChanged(const std::string &newName);

private slots:
    void onSaveClicked();

private:
    User &user_;
    QLineEdit *nameInput;
    QLabel *idLabel;
};

#endif // PROFILEWINDOW_HPP