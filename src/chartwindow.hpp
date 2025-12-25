#ifndef CHARTWINDOW_HPP
#define CHARTWINDOW_HPP

#include <QWidget>
#include <QComboBox>
#include <QtCharts/QChartView>
#include "user.hpp"

class ChartWindow : public QWidget {
    Q_OBJECT

public:
    explicit ChartWindow(const User &user, QWidget *parent = nullptr);

private slots:
    void updateChart();
    void onExportClicked();
    void onPrintClicked();
    void onEmailClicked();

private:
    User user_;
    QComboBox *accountCombo;
    QChartView *chartView;
};

#endif // CHARTWINDOW_HPP