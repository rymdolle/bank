#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QSplashScreen>
#include <QPixmap>
#include <QThread>
#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Splash Screen setup
    QPixmap pixmap("data/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents(); // Ensure the splash screen is drawn immediately

    // Simulate loading time (2 seconds) so the splash screen is visible
    QThread::sleep(2);

    // Set application icon (Ensure you have 'icon.png' in your data directory)
    app.setWindowIcon(QIcon("data/icon.png"));

    // Load custom font (Ensure you have 'CustomFont.ttf' in your data directory)
    int id = QFontDatabase::addApplicationFont("data/CustomFont.ttf");
    if (id != -1) {
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont font(family);
        font.setPointSize(10); // Set default font size
        app.setFont(font);
    }

    app.setStyleSheet(
        "QPushButton {"
        "    background-color: #007BFF;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 6px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #0056b3; }"
        "QPushButton:pressed { background-color: #004085; }"
        "QPushButton:disabled { background-color: #cccccc; color: #666666; }"
    );

    MainWindow window;
    window.show();
    splash.finish(&window); // Close the splash screen when the main window is shown

    return app.exec();
}