#include "settingswindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>

SettingsWindow::SettingsWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Settings");

    layout->addWidget(new QLabel("Select Application Theme:", this));

    auto addThemeBtn = [&](const QString &name, const QString &c, const QString &h, const QString &p) {
        QPushButton *btn = new QPushButton(name, this);
        btn->setProperty("color", c);
        btn->setProperty("hover", h);
        btn->setProperty("pressed", p);
        // Style the button itself to look like the theme
        btn->setStyleSheet(QString(
            "background-color: %1; color: white; border-radius: 5px; padding: 6px; font-weight: bold;"
        ).arg(c));
        layout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, &SettingsWindow::onThemeClicked);
    };

    addThemeBtn("Blue (Default)", "#007BFF", "#0056b3", "#004085");
    addThemeBtn("Red", "#DC3545", "#c82333", "#bd2130");
    addThemeBtn("Green", "#28A745", "#218838", "#1e7e34");
    addThemeBtn("Purple", "#6f42c1", "#5a32a3", "#48258b");
    addThemeBtn("Dark Gray", "#343a40", "#23272b", "#1d2124");
    addThemeBtn("Orange", "#fd7e14", "#e36d0c", "#ca5f08");

    resize(300, 400);
}

void SettingsWindow::onThemeClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString c = btn->property("color").toString();
    QString h = btn->property("hover").toString();
    QString p = btn->property("pressed").toString();

    QString style = QString(
        "QPushButton {"
        "    background-color: %1;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 6px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: %2; }"
        "QPushButton:pressed { background-color: %3; }"
        "QPushButton:disabled { background-color: #cccccc; color: #666666; }"
    ).arg(c, h, p);

    qApp->setStyleSheet(style);
}