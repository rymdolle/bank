#include "notificationwindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QStringList>

NotificationWindow::NotificationWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Notifications");

    layout->addWidget(new QLabel("Your Notifications:", this));
    notificationList = new QListWidget(this);
    layout->addWidget(notificationList);

    QFile file("data/notifications.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(':');
            if (parts.size() >= 2) {
                if (parts[0].toInt() == user_.getId()) {
                    // Reconstruct message (UserId:Message)
                    QString msg = parts.mid(1).join(':'); 
                    notificationList->addItem(msg);
                }
            }
        }
        file.close();
    }
    
    if (notificationList->count() == 0) {
        notificationList->addItem("No notifications.");
    }

    resize(400, 300);
}