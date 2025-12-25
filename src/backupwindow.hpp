#ifndef BACKUPWINDOW_HPP
#define BACKUPWINDOW_HPP

#include <QWidget>

class BackupWindow : public QWidget {
    Q_OBJECT
public:
    explicit BackupWindow(QWidget *parent = nullptr);

private slots:
    void onBackupClicked();
};

#endif // BACKUPWINDOW_HPP