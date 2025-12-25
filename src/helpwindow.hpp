#ifndef HELPWINDOW_HPP
#define HELPWINDOW_HPP

#include <QWidget>
#include <QTextBrowser>

class HelpWindow : public QWidget {
    Q_OBJECT
public:
    explicit HelpWindow(QWidget *parent = nullptr);

private:
    QTextBrowser *textBrowser;
};

#endif // HELPWINDOW_HPP