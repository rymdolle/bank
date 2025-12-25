#ifndef RESTOREWINDOW_HPP
#define RESTOREWINDOW_HPP

#include <QWidget>

class RestoreWindow : public QWidget {
    Q_OBJECT
public:
    explicit RestoreWindow(QWidget *parent = nullptr);

private slots:
    void onRestoreClicked();
};

#endif // RESTOREWINDOW_HPP