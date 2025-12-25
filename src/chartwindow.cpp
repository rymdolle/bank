#include "chartwindow.hpp"
#include "currency.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDateTime>
#include <QtCharts>
#include <QPainter>
#include <algorithm>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QFileInfo>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QInputDialog>

// using namespace QtCharts;

struct TransactionRecord {
    QDateTime date;
    double amountChange;
};

ChartWindow::ChartWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Balance History");

    layout->addWidget(new QLabel("Select Account:", this));
    accountCombo = new QComboBox(this);
    for (const auto &acc : user_.getAccounts()) {
        accountCombo->addItem(QString::fromStdString(acc.getAccountName()), QVariant(acc.getId()));
    }
    connect(accountCombo, &QComboBox::currentIndexChanged, this, &ChartWindow::updateChart);
    layout->addWidget(accountCombo);

    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);

    QPushButton *exportBtn = new QPushButton("Export Chart as Image", this);
    layout->addWidget(exportBtn);
    connect(exportBtn, &QPushButton::clicked, this, &ChartWindow::onExportClicked);

    QPushButton *printBtn = new QPushButton("Print Chart", this);
    layout->addWidget(printBtn);
    connect(printBtn, &QPushButton::clicked, this, &ChartWindow::onPrintClicked);

    QPushButton *emailBtn = new QPushButton("Email Chart", this);
    layout->addWidget(emailBtn);
    connect(emailBtn, &QPushButton::clicked, this, &ChartWindow::onEmailClicked);

    resize(800, 600);
    updateChart();
}

void ChartWindow::updateChart() {
    if (accountCombo->currentIndex() < 0) return;
    int accountId = accountCombo->currentData().toInt();

    // Find current balance and currency
    double currentBalance = 0.0;
    std::string currencyType;
    for (const auto &acc : user_.getAccounts()) {
        if (acc.getId() == accountId) {
            currentBalance = acc.getBalance();
            currencyType = acc.getCurrency();
            break;
        }
    }

    // Read transactions
    QFile file("data/transactions.txt");
    std::vector<TransactionRecord> history;
    
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QRegularExpression transferRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Transferred (.+) from Account (\\d+) to Account (\\d+)$");
        QRegularExpression depositRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Deposited (.+) to Account (\\d+)$");
        QRegularExpression withdrawRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Withdrew (.+) from Account (\\d+)$");
        QRegularExpression interestRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Interest Applied (.+) to Account (\\d+)$");
        QRegularExpression loanRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Loan Approved (.+) to Account (\\d+)$");

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QRegularExpressionMatch match;
            double change = 0.0;
            QString dateStr;
            bool relevant = false;

            if ((match = transferRegex.match(line)).hasMatch()) {
                dateStr = match.captured(1);
                int src = match.captured(4).toInt();
                int dst = match.captured(5).toInt();
                double amount = (double)Currency::get(currencyType).parse(match.captured(3).toStdString());
                if (src == accountId) { change = -amount; relevant = true; }
                else if (dst == accountId) { change = amount; relevant = true; }
            } else if ((match = depositRegex.match(line)).hasMatch()) {
                dateStr = match.captured(1);
                if (match.captured(4).toInt() == accountId) {
                    change = (double)Currency::get(currencyType).parse(match.captured(3).toStdString());
                    relevant = true;
                }
            } else if ((match = withdrawRegex.match(line)).hasMatch()) {
                dateStr = match.captured(1);
                if (match.captured(4).toInt() == accountId) {
                    change = -(double)Currency::get(currencyType).parse(match.captured(3).toStdString());
                    relevant = true;
                }
            } else if ((match = interestRegex.match(line)).hasMatch()) {
                dateStr = match.captured(1);
                if (match.captured(4).toInt() == accountId) {
                    change = (double)Currency::get(currencyType).parse(match.captured(3).toStdString());
                    relevant = true;
                }
            } else if ((match = loanRegex.match(line)).hasMatch()) {
                dateStr = match.captured(1);
                if (match.captured(4).toInt() == accountId) {
                    change = (double)Currency::get(currencyType).parse(match.captured(3).toStdString());
                    relevant = true;
                }
            }

            if (relevant && !dateStr.isEmpty()) {
                QDateTime dt = QDateTime::fromString(dateStr, "yyyy-MM-dd hh:mm:ss");
                if (dt.isValid()) {
                    history.push_back({dt, change});
                }
            }
        }
        file.close();
    }

    // Reconstruct balance history working backwards
    QLineSeries *series = new QLineSeries();
    series->setName("Balance");
    
    // Add current state
    series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), currentBalance);

    // Process history in reverse (newest to oldest)
    double runningBalance = currentBalance;
    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        runningBalance -= it->amountChange;
        series->append(it->date.toMSecsSinceEpoch(), runningBalance);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Account Balance Over Time");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(5);
    axisX->setFormat("MMM dd");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Balance");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView->setChart(chart);
}

void ChartWindow::onExportClicked() {
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this, "Save Chart", "", "PNG Image (*.png);;JPEG Image (*.jpg)", &selectedFilter);
    if (fileName.isEmpty()) return;

    if (QFileInfo(fileName).suffix().isEmpty()) {
        if (selectedFilter.contains("jpg", Qt::CaseInsensitive)) fileName += ".jpg";
        else fileName += ".png";
    }

    QPixmap p = chartView->grab();
    if (p.save(fileName)) {
        QMessageBox::information(this, "Success", "Chart exported successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save chart image.");
    }
}

void ChartWindow::onPrintClicked() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageOrientation(QPageLayout::Landscape);
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        double xscale = printer.pageLayout().paintRectPixels(printer.resolution()).width() / double(chartView->width());
        double yscale = printer.pageLayout().paintRectPixels(printer.resolution()).height() / double(chartView->height());
        double scale = std::min(xscale, yscale);
        painter.scale(scale, scale);
        chartView->render(&painter);
    }
}

void ChartWindow::onEmailClicked() {
    bool ok;
    QString email = QInputDialog::getText(this, "Email Chart",
                                         "Recipient Email:", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !email.isEmpty()) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        QString filename = "data/chart_" + timestamp + ".png";
        if (chartView->grab().save(filename)) {
            QFile file("data/sent_emails.txt");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "] Sent chart (" << filename << ") to " << email << "\n";
                file.close();
            }
            QMessageBox::information(this, "Success", "Email sent successfully to " + email + "!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to generate chart image for email.");
        }
    }
}