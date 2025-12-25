#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include "user.hpp"

class SettingsWindow : public QWidget {
    Q_OBJECT
public:
    explicit SettingsWindow(const User &user, QWidget *parent = nullptr);

private slots:
    void onThemeClicked();

private:
    User user_;
};

#endif // SETTINGSWINDOW_HPP