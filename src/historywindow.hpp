#ifndef HISTORYWINDOW_HPP
#define HISTORYWINDOW_HPP

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>
#include "user.hpp"

class HistoryWindow : public QWidget {
    Q_OBJECT
public:
    explicit HistoryWindow(const User &user, QWidget *parent = nullptr);
    void refresh();

private slots:
    void onExportClicked();
    void onImportClicked();
    void onSortClicked();
    void onPrintClicked();

private:
    QListWidget *historyList;
    QLineEdit *searchInput;
    QCheckBox *dateFilterCheck;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    User user_;
    bool newestFirst = false;
    QPushButton *sortBtn;
};

#endif // HISTORYWINDOW_HPP