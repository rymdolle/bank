#ifndef NOTIFICATIONWINDOW_HPP
#define NOTIFICATIONWINDOW_HPP

#include <QWidget>
#include <QListWidget>
#include "user.hpp"

class NotificationWindow : public QWidget {
    Q_OBJECT
public:
    explicit NotificationWindow(const User &user, QWidget *parent = nullptr);

private:
    User user_;
    QListWidget *notificationList;
};

#endif // NOTIFICATIONWINDOW_HPP