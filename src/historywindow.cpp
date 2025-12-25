#include "historywindow.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QLineEdit>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>

HistoryWindow::HistoryWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Transaction History");

    layout->addWidget(new QLabel("Search:", this));
    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("Filter by Account ID or Amount...");
    layout->addWidget(searchInput);
    connect(searchInput, &QLineEdit::textChanged, this, &HistoryWindow::refresh);

    QHBoxLayout *dateLayout = new QHBoxLayout();
    dateFilterCheck = new QCheckBox("Filter by Date:", this);
    dateLayout->addWidget(dateFilterCheck);

    startDateEdit = new QDateEdit(QDate::currentDate().addMonths(-1), this);
    startDateEdit->setCalendarPopup(true);
    startDateEdit->setEnabled(false);
    dateLayout->addWidget(startDateEdit);

    dateLayout->addWidget(new QLabel("to", this));

    endDateEdit = new QDateEdit(QDate::currentDate(), this);
    endDateEdit->setCalendarPopup(true);
    endDateEdit->setEnabled(false);
    dateLayout->addWidget(endDateEdit);

    layout->addLayout(dateLayout);

    layout->addWidget(new QLabel("Transaction Log:", this));
    historyList = new QListWidget(this);
    layout->addWidget(historyList);

    sortBtn = new QPushButton("Sort: Oldest First", this);
    layout->addWidget(sortBtn);
    connect(sortBtn, &QPushButton::clicked, this, &HistoryWindow::onSortClicked);

    QPushButton *exportBtn = new QPushButton("Export to CSV", this);
    layout->addWidget(exportBtn);
    connect(exportBtn, &QPushButton::clicked, this, &HistoryWindow::onExportClicked);

    QPushButton *importBtn = new QPushButton("Import from CSV", this);
    layout->addWidget(importBtn);
    connect(importBtn, &QPushButton::clicked, this, &HistoryWindow::onImportClicked);

    QPushButton *printBtn = new QPushButton("Print Receipt", this);
    layout->addWidget(printBtn);
    connect(printBtn, &QPushButton::clicked, this, &HistoryWindow::onPrintClicked);

    connect(dateFilterCheck, &QCheckBox::toggled, this, [this](bool checked){
        startDateEdit->setEnabled(checked);
        endDateEdit->setEnabled(checked);
        refresh();
    });
    connect(startDateEdit, &QDateEdit::dateChanged, this, &HistoryWindow::refresh);
    connect(endDateEdit, &QDateEdit::dateChanged, this, &HistoryWindow::refresh);

    refresh();
    resize(400, 300);
}

void HistoryWindow::onSortClicked() {
    newestFirst = !newestFirst;
    sortBtn->setText(newestFirst ? "Sort: Newest First" : "Sort: Oldest First");
    refresh();
}

void HistoryWindow::refresh() {
    historyList->clear();
    QFile file("data/transactions.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QStringList lines;
        QString filter = searchInput->text();
        bool filterDate = dateFilterCheck->isChecked();
        QDate start = startDateEdit->date();
        QDate end = endDateEdit->date();
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            bool relevant = false;
            for (const auto &acc : user_.getAccounts()) {
                QString idStr = QString::number(acc.getId());
                // Check if the account ID appears as source (followed by space) or destination (at end of line)
                if (line.contains("Account " + idStr + " ") || line.endsWith("Account " + idStr)) {
                    relevant = true;
                    break;
                }
            }

            if (relevant && filterDate) {
                QRegularExpression dateRegex("^\\[(.*?)\\]");
                QRegularExpressionMatch match = dateRegex.match(line);
                if (match.hasMatch()) {
                    QString dateStr = match.captured(1);
                    QDateTime dt = QDateTime::fromString(dateStr, "yyyy-MM-dd hh:mm:ss");
                    if (dt.isValid()) {
                        if (dt.date() < start || dt.date() > end) relevant = false;
                    }
                }
            }
            
            if (relevant && !filter.isEmpty() && !line.contains(filter, Qt::CaseInsensitive)) {
                relevant = false;
            }

            if (relevant) lines.append(line);
        }
        
        if (newestFirst) {
            std::reverse(lines.begin(), lines.end());
        }
        if (lines.isEmpty()) {
            historyList->addItem("No transactions found for your accounts.");
        } else {
            historyList->addItems(lines);
        }
        file.close();
    } else {
        historyList->addItem("No transactions found.");
    }
}

void HistoryWindow::onExportClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile outFile(fileName);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open file for writing.");
        return;
    }

    QTextStream out(&outFile);
    out << "Date,Category,Type,Amount,From Account,To Account\n";

    QFile inFile("data/transactions.txt");
    if (inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&inFile);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;

            bool relevant = false;
            for (const auto &acc : user_.getAccounts()) {
                QString idStr = QString::number(acc.getId());
                if (line.contains("Account " + idStr + " ") || line.endsWith("Account " + idStr)) {
                    relevant = true;
                    break;
                }
            }

            if (relevant) {
                QRegularExpression transferRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Transferred (.+) from Account (\\d+) to Account (\\d+)$");
                QRegularExpression depositRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Deposited (.+) to Account (\\d+)$");
                QRegularExpression withdrawRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Withdrew (.+) from Account (\\d+)$");
                QRegularExpression interestRegex("^(?:\\[(.*?)\\] )?(?:\\[(.*?)\\] )?Interest Applied (.+) to Account (\\d+)$");
                
                QRegularExpressionMatch match;
                if ((match = transferRegex.match(line)).hasMatch()) {
                    out << match.captured(1) << "," << match.captured(2) << ",Transfer," << match.captured(3) << "," << match.captured(4) << "," << match.captured(5) << "\n";
                } else if ((match = depositRegex.match(line)).hasMatch()) {
                    out << match.captured(1) << "," << match.captured(2) << ",Deposit," << match.captured(3) << ",-," << match.captured(4) << "\n";
                } else if ((match = withdrawRegex.match(line)).hasMatch()) {
                    out << match.captured(1) << "," << match.captured(2) << ",Withdrawal," << match.captured(3) << "," << match.captured(4) << ",-\n";
                } else if ((match = interestRegex.match(line)).hasMatch()) {
                    out << match.captured(1) << "," << match.captured(2) << ",Interest," << match.captured(3) << ",-," << match.captured(4) << "\n";
                }
            }
        }
        inFile.close();
    }
    outFile.close();
    QMessageBox::information(this, "Success", "Export successful!");
}

void HistoryWindow::onImportClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile inFile(fileName);
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open file for reading.");
        return;
    }

    QFile outFile("data/transactions.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open transactions log for writing.");
        return;
    }

    QTextStream in(&inFile);
    QTextStream out(&outFile);

    // Skip header
    if (!in.atEnd()) in.readLine();

    int count = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');
        if (parts.size() < 5) continue;

        QString date = parts[0];
        QString category = "";
        QString type, amount, from, to;

        if (parts.size() >= 6) {
             category = parts[1];
             type = parts[2];
             amount = parts[3];
             from = parts[4];
             to = parts[5];
        } else {
             type = parts[1];
             amount = parts[2];
             from = parts[3];
             to = parts[4];
        }

        QString catStr = category.isEmpty() ? "" : "[" + category + "] ";
        
        QString logEntry;
        if (type == "Transfer") {
            logEntry = QString("[%1] %2Transferred %3 from Account %4 to Account %5").arg(date, catStr, amount, from, to);
        } else if (type == "Deposit") {
            logEntry = QString("[%1] %2Deposited %3 to Account %4").arg(date, catStr, amount, to);
        } else if (type == "Withdrawal") {
            logEntry = QString("[%1] %2Withdrew %3 from Account %4").arg(date, catStr, amount, from);
        } else if (type == "Interest") {
            logEntry = QString("[%1] %2Interest Applied %3 to Account %4").arg(date, catStr, amount, to);
        }

        if (!logEntry.isEmpty()) {
            out << logEntry << "\n";
            count++;
        }
    }

    inFile.close();
    outFile.close();
    refresh();
    QMessageBox::information(this, "Success", QString("Imported %1 transactions.").arg(count));
}

void HistoryWindow::onPrintClicked() {
    QListWidgetItem *item = historyList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Error", "Please select a transaction to print.");
        return;
    }

    QString transactionDetails = item->text();
    if (transactionDetails == "No transactions found for your accounts." || transactionDetails == "No transactions found.") {
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QTextDocument doc;
        QString html = "<h1 align='center'>Bank Transaction Receipt</h1>";
        html += "<hr>";
        html += "<p><b>Date:</b> " + QDateTime::currentDateTime().toString() + "</p>";
        html += "<p><b>Details:</b></p>";
        html += "<p>" + transactionDetails + "</p>";
        html += "<hr>";
        html += "<p align='center'><i>Thank you for banking with us!</i></p>";
        
        doc.setHtml(html);
        doc.print(&printer);
    }
}