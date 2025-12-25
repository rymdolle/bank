#include "dashboardwindow.hpp"
#include "currency.hpp"
#include "transferwindow.hpp"
#include "historywindow.hpp"
#include "createaccountwindow.hpp"
#include "changepasswordwindow.hpp"
#include "depositwindow.hpp"
#include "interestwindow.hpp"
#include "withdrawwindow.hpp"
#include "profilewindow.hpp"
#include "loanwindow.hpp"
#include "chartwindow.hpp"
#include "notificationwindow.hpp"
#include "recurringtransferwindow.hpp"
#include "budgetwindow.hpp"
#include "supportwindow.hpp"
#include "settingswindow.hpp"
#include "backupwindow.hpp"
#include "restorewindow.hpp"
#include "helpwindow.hpp"
#include <QDateTime>
#include <QString>
#include <QMessageBox>
#include <QApplication>
#include <QStyleFactory>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QFileDialog>

DashboardWindow::DashboardWindow(const User &user, QWidget *parent)
    : QWidget(parent), user_(user) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Welcome Label
    welcomeLabel = new QLabel("Welcome " + QString::fromStdString(user_.getName()) + "!", this);
    QFont font = welcomeLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    welcomeLabel->setFont(font);
    layout->addWidget(welcomeLabel);

    // Accounts List
    layout->addWidget(new QLabel("Your Accounts:", this));
    accountsList = new QListWidget(this);
    refreshAccountList();
    layout->addWidget(accountsList);

    QPushButton *transferBtn = new QPushButton("Transfer Money", this);
    layout->addWidget(transferBtn);
    connect(transferBtn, &QPushButton::clicked, this, &DashboardWindow::onTransferClicked);

    QPushButton *recurringBtn = new QPushButton("Schedule Recurring Transfer", this);
    layout->addWidget(recurringBtn);
    connect(recurringBtn, &QPushButton::clicked, this, &DashboardWindow::onRecurringTransferClicked);

    QPushButton *budgetBtn = new QPushButton("Set Budget", this);
    layout->addWidget(budgetBtn);
    connect(budgetBtn, &QPushButton::clicked, this, &DashboardWindow::onBudgetClicked);

    QPushButton *darkModeBtn = new QPushButton("Toggle Dark Mode", this);
    layout->addWidget(darkModeBtn);
    connect(darkModeBtn, &QPushButton::clicked, this, &DashboardWindow::onDarkModeClicked);

    QPushButton *supportBtn = new QPushButton("Contact Support", this);
    layout->addWidget(supportBtn);
    connect(supportBtn, &QPushButton::clicked, this, &DashboardWindow::onSupportClicked);

    QPushButton *helpBtn = new QPushButton("Help / Manual", this);
    layout->addWidget(helpBtn);
    connect(helpBtn, &QPushButton::clicked, this, &DashboardWindow::onHelpClicked);

    QPushButton *settingsBtn = new QPushButton("Settings (Theme)", this);
    layout->addWidget(settingsBtn);
    connect(settingsBtn, &QPushButton::clicked, this, &DashboardWindow::onSettingsClicked);

    QPushButton *backupBtn = new QPushButton("Backup Data", this);
    layout->addWidget(backupBtn);
    connect(backupBtn, &QPushButton::clicked, this, &DashboardWindow::onBackupClicked);

    QPushButton *restoreBtn = new QPushButton("Restore Data", this);
    layout->addWidget(restoreBtn);
    connect(restoreBtn, &QPushButton::clicked, this, &DashboardWindow::onRestoreClicked);

    QPushButton *exportPdfBtn = new QPushButton("Export Accounts to PDF", this);
    layout->addWidget(exportPdfBtn);
    connect(exportPdfBtn, &QPushButton::clicked, this, &DashboardWindow::onExportAccountsClicked);

    QPushButton *depositBtn = new QPushButton("Deposit Funds", this);
    layout->addWidget(depositBtn);
    connect(depositBtn, &QPushButton::clicked, this, &DashboardWindow::onDepositClicked);

    QPushButton *withdrawBtn = new QPushButton("Withdraw Funds", this);
    layout->addWidget(withdrawBtn);
    connect(withdrawBtn, &QPushButton::clicked, this, &DashboardWindow::onWithdrawClicked);

    QPushButton *loanBtn = new QPushButton("Request Loan", this);
    layout->addWidget(loanBtn);
    connect(loanBtn, &QPushButton::clicked, this, &DashboardWindow::onLoanClicked);

    QPushButton *interestBtn = new QPushButton("Calculate Interest", this);
    layout->addWidget(interestBtn);
    connect(interestBtn, &QPushButton::clicked, this, &DashboardWindow::onInterestClicked);

    QPushButton *createBtn = new QPushButton("Create Account", this);
    layout->addWidget(createBtn);
    connect(createBtn, &QPushButton::clicked, this, &DashboardWindow::onCreateAccountClicked);

    QPushButton *historyBtn = new QPushButton("Transaction History", this);
    layout->addWidget(historyBtn);
    connect(historyBtn, &QPushButton::clicked, this, &DashboardWindow::onHistoryClicked);

    QPushButton *chartBtn = new QPushButton("Balance History (Chart)", this);
    layout->addWidget(chartBtn);
    connect(chartBtn, &QPushButton::clicked, this, &DashboardWindow::onChartClicked);

    QPushButton *notifyBtn = new QPushButton("Notifications", this);
    layout->addWidget(notifyBtn);
    connect(notifyBtn, &QPushButton::clicked, this, &DashboardWindow::onNotificationsClicked);

    QPushButton *deleteBtn = new QPushButton("Delete Account", this);
    layout->addWidget(deleteBtn);
    connect(deleteBtn, &QPushButton::clicked, this, &DashboardWindow::onDeleteAccountClicked);

    QPushButton *changePassBtn = new QPushButton("Change Password", this);
    layout->addWidget(changePassBtn);
    connect(changePassBtn, &QPushButton::clicked, this, &DashboardWindow::onChangePasswordClicked);

    QPushButton *profileBtn = new QPushButton("Profile", this);
    layout->addWidget(profileBtn);
    connect(profileBtn, &QPushButton::clicked, this, &DashboardWindow::onProfileClicked);

    QPushButton *logoutBtn = new QPushButton("Logout", this);
    layout->addWidget(logoutBtn);
    connect(logoutBtn, &QPushButton::clicked, this, &DashboardWindow::onLogoutClicked);

    resize(400, 300);

    processRecurringTransfers();
}

DashboardWindow::~DashboardWindow() {
    if (transferWindow) delete transferWindow;
    if (historyWindow) delete historyWindow;
    if (createAccountWindow) delete createAccountWindow;
    if (changePasswordWindow) delete changePasswordWindow;
    if (depositWindow) delete depositWindow;
    if (interestWindow) delete interestWindow;
    if (withdrawWindow) delete withdrawWindow;
    if (profileWindow) delete profileWindow;
    if (loanWindow) delete loanWindow;
    if (chartWindow) delete chartWindow;
    if (notificationWindow) delete notificationWindow;
    if (recurringTransferWindow) delete recurringTransferWindow;
    if (budgetWindow) delete budgetWindow;
    if (supportWindow) delete supportWindow;
    if (settingsWindow) delete settingsWindow;
    if (backupWindow) delete backupWindow;
    if (restoreWindow) delete restoreWindow;
    if (helpWindow) delete helpWindow;
}

void DashboardWindow::onTransferClicked() {
    if (transferWindow) delete transferWindow;
    transferWindow = new TransferWindow(user_);
    connect(transferWindow, &TransferWindow::transferSuccess, this, &DashboardWindow::onTransferSuccess);
    transferWindow->show();
}

void DashboardWindow::onRecurringTransferClicked() {
    if (recurringTransferWindow) delete recurringTransferWindow;
    recurringTransferWindow = new RecurringTransferWindow(user_);
    recurringTransferWindow->show();
}

void DashboardWindow::onBudgetClicked() {
    if (budgetWindow) delete budgetWindow;
    budgetWindow = new BudgetWindow(user_);
    budgetWindow->show();
}

void DashboardWindow::onSupportClicked() {
    if (supportWindow) delete supportWindow;
    supportWindow = new SupportWindow(user_);
    supportWindow->show();
}

void DashboardWindow::onHelpClicked() {
    if (helpWindow) delete helpWindow;
    helpWindow = new HelpWindow();
    helpWindow->show();
}

void DashboardWindow::onSettingsClicked() {
    if (settingsWindow) delete settingsWindow;
    settingsWindow = new SettingsWindow(user_);
    settingsWindow->show();
}

void DashboardWindow::onBackupClicked() {
    if (backupWindow) delete backupWindow;
    backupWindow = new BackupWindow();
    backupWindow->show();
}

void DashboardWindow::onRestoreClicked() {
    if (restoreWindow) delete restoreWindow;
    restoreWindow = new RestoreWindow();
    restoreWindow->show();
}

void DashboardWindow::onExportAccountsClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Accounts", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QString html = "<h1 align='center'>Account Statement</h1>";
    html += "<h3 align='center'>User: " + QString::fromStdString(user_.getName()) + "</h3>";
    html += "<hr>";
    html += "<table width='100%' border='1' cellspacing='0' cellpadding='5'>";
    html += "<tr><th>Account Name</th><th>Balance</th></tr>";

    for (const auto &acc : user_.getAccounts()) {
        html += "<tr>";
        html += "<td>" + QString::fromStdString(acc.getAccountName()) + "</td>";
        html += "<td>" + QString::fromStdString(Currency::get(acc.getCurrency()).format(acc.getBalance())) + "</td>";
        html += "</tr>";
    }
    html += "</table>";
    html += "<br><p>Generated on: " + QDateTime::currentDateTime().toString() + "</p>";

    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(this, "Success", "Accounts exported to PDF successfully!");
}

void DashboardWindow::onDarkModeClicked() {
    isDarkMode = !isDarkMode;
    if (isDarkMode) {
        qApp->setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        qApp->setPalette(darkPalette);
    } else {
        qApp->setPalette(qApp->style()->standardPalette());
    }
}

void DashboardWindow::onHistoryClicked() {
    if (historyWindow) delete historyWindow;
    historyWindow = new HistoryWindow(user_);
    historyWindow->show();
}

void DashboardWindow::onChartClicked() {
    if (chartWindow) delete chartWindow;
    chartWindow = new ChartWindow(user_);
    chartWindow->show();
}

void DashboardWindow::onNotificationsClicked() {
    if (notificationWindow) delete notificationWindow;
    notificationWindow = new NotificationWindow(user_);
    notificationWindow->show();
}

void DashboardWindow::onLogoutClicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit logout();
        this->close();
    }
}

void DashboardWindow::onDeleteAccountClicked() {
    int currentRow = accountsList->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Error", "Please select an account to delete.");
        return;
    }

    auto& accounts = user_.getAccounts();
    if (currentRow >= accounts.size()) return;

    int accountId = accounts[currentRow].getId();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this account?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) return;

    // Remove from file
    std::ifstream inFile("data/accounts.txt");
    if (!inFile.is_open()) {
        QMessageBox::critical(this, "Error", "Could not open accounts database.");
        return;
    }
    std::ofstream outFile("data/accounts_temp.txt");

    std::string line;
    while (std::getline(inFile, line)) {
        bool isTarget = false;
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;
        while(std::getline(ss, segment, ':')) parts.push_back(segment);

        if (parts.size() >= 2) {
             // Check for UserID:AccountID format or AccountID:UserID
             try {
                 if ((std::stoi(parts[0]) == user_.getId() && std::stoi(parts[1]) == accountId) ||
                     (std::stoi(parts[0]) == accountId && std::stoi(parts[1]) == user_.getId())) {
                     isTarget = true;
                 }
             } catch (...) {}
        }

        if (!isTarget) outFile << line << "\n";
    }
    inFile.close();
    outFile.close();

    std::remove("data/accounts.txt");
    std::rename("data/accounts_temp.txt", "data/accounts.txt");

    // Update memory and UI
    accounts.erase(accounts.begin() + currentRow);
    refreshAccountList();
}

void DashboardWindow::onCreateAccountClicked() {
    if (createAccountWindow) delete createAccountWindow;
    createAccountWindow = new CreateAccountWindow(user_);
    connect(createAccountWindow, &CreateAccountWindow::accountCreated, this, &DashboardWindow::onAccountCreated);
    createAccountWindow->show();
}

void DashboardWindow::onAccountCreated(const Account &account) {
    user_.createAccount(account);
    refreshAccountList();
}

void DashboardWindow::onChangePasswordClicked() {
    if (changePasswordWindow) delete changePasswordWindow;
    changePasswordWindow = new ChangePasswordWindow(user_);
    changePasswordWindow->show();
}

void DashboardWindow::onDepositClicked() {
    if (depositWindow) delete depositWindow;
    depositWindow = new DepositWindow(user_);
    connect(depositWindow, &DepositWindow::depositSuccess, this, &DashboardWindow::onDepositSuccess);
    depositWindow->show();
}

void DashboardWindow::onDepositSuccess(int accountId, int amount) {
    for (auto &acc : user_.getAccounts()) {
        if (acc.getId() == accountId) {
            acc.setBalance(acc.getBalance() + amount);
        }
    }
    refreshAccountList();
}

void DashboardWindow::onInterestClicked() {
    if (interestWindow) delete interestWindow;
    interestWindow = new InterestWindow(user_);
    connect(interestWindow, &InterestWindow::interestApplied, this, &DashboardWindow::onInterestApplied);
    interestWindow->show();
}

void DashboardWindow::onInterestApplied(int accountId, int amount) {
    for (auto &acc : user_.getAccounts()) {
        if (acc.getId() == accountId) {
            acc.setBalance(acc.getBalance() + amount);
        }
    }
    refreshAccountList();
}

void DashboardWindow::onWithdrawClicked() {
    if (withdrawWindow) delete withdrawWindow;
    withdrawWindow = new WithdrawWindow(user_);
    connect(withdrawWindow, &WithdrawWindow::withdrawSuccess, this, &DashboardWindow::onWithdrawSuccess);
    withdrawWindow->show();
}

void DashboardWindow::onWithdrawSuccess(int accountId, int amount) {
    for (auto &acc : user_.getAccounts()) {
        if (acc.getId() == accountId) {
            acc.setBalance(acc.getBalance() - amount);
        }
    }
    refreshAccountList();
}

void DashboardWindow::onProfileClicked() {
    if (profileWindow) delete profileWindow;
    profileWindow = new ProfileWindow(user_);
    connect(profileWindow, &ProfileWindow::nameChanged, this, &DashboardWindow::onNameChanged);
    profileWindow->show();
}

void DashboardWindow::onNameChanged(const std::string &newName) {
    welcomeLabel->setText("Welcome " + QString::fromStdString(newName) + "!");
}

void DashboardWindow::onLoanClicked() {
    if (loanWindow) delete loanWindow;
    loanWindow = new LoanWindow(user_);
    connect(loanWindow, &LoanWindow::loanApproved, this, &DashboardWindow::onLoanApproved);
    loanWindow->show();
}

void DashboardWindow::onLoanApproved(int accountId, int amount) {
    for (auto &acc : user_.getAccounts()) {
        if (acc.getId() == accountId) {
            acc.setBalance(acc.getBalance() + amount);
        }
    }
    refreshAccountList();
}

void DashboardWindow::onTransferSuccess(int srcId, int dstId, int amount) {
    // Update the local user object's account balances
    for (auto &acc : user_.getAccounts()) {
        if (acc.getId() == srcId) {
            acc.setBalance(acc.getBalance() - amount);
        }
        if (acc.getId() == dstId) {
            acc.setBalance(acc.getBalance() + amount);
        }
    }
    refreshAccountList();
}

void DashboardWindow::refreshAccountList() {
    accountsList->clear();
    for (auto &acc : user_.getAccounts()) {
        std::string balance = Currency::get(acc.getCurrency()).format(acc.getBalance());
        QString itemText = QString::fromStdString(acc.getAccountName()) + " - " + QString::fromStdString(balance);
        accountsList->addItem(itemText);
    }
}

void DashboardWindow::processRecurringTransfers() {
    std::ifstream inFile("data/recurring_transfers.txt");
    if (!inFile.is_open()) return;

    std::vector<std::string> lines;
    std::string line;
    bool changesMade = false;
    qint64 now = QDateTime::currentDateTime().toSecsSinceEpoch();

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;
        while(std::getline(ss, segment, ':')) parts.push_back(segment);

        if (parts.size() >= 7) {
            int uId = std::stoi(parts[0]);
            if (uId == user_.getId()) {
                qint64 nextRun = std::stoll(parts[5]);
                if (now >= nextRun) {
                    int srcId = std::stoi(parts[1]);
                    int dstId = std::stoi(parts[2]);
                    int amount = std::stoi(parts[3]);
                    int interval = std::stoi(parts[4]);
                    int remaining = std::stoi(parts[6]);

                    bool fundsAvailable = false;
                    for(const auto& acc : user_.getAccounts()) {
                        if(acc.getId() == srcId && acc.getBalance() >= amount) {
                            fundsAvailable = true; 
                            break;
                        }
                    }

                    if (fundsAvailable && Account::transferingMoney(srcId, dstId, amount, uId)) {
                        std::ofstream logFile("data/transactions.txt", std::ios::app);
                        if (logFile.is_open()) {
                             logFile << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << "] Recurring Transfer " 
                                     << amount << " from Account " << srcId << " to Account " << dstId << "\n";
                        }
                        
                        for(auto& acc : user_.getAccounts()) {
                            if(acc.getId() == srcId) acc.setBalance(acc.getBalance() - amount);
                            if(acc.getId() == dstId) acc.setBalance(acc.getBalance() + amount);
                        }
                        changesMade = true;

                        remaining--;
                        nextRun += (interval * 24 * 3600);
                    }
                    
                    if (remaining > 0) {
                        std::string newLine = parts[0] + ":" + parts[1] + ":" + parts[2] + ":" + parts[3] + ":" + parts[4] + ":" + std::to_string(nextRun) + ":" + std::to_string(remaining);
                        lines.push_back(newLine);
                    }
                } else {
                    lines.push_back(line);
                }
            } else {
                lines.push_back(line);
            }
        }
    }
    inFile.close();

    if (changesMade) {
        std::ofstream outFile("data/recurring_transfers.txt");
        for (const auto& l : lines) outFile << l << "\n";
        refreshAccountList();
        QMessageBox::information(this, "Recurring Transfer", "One or more recurring transfers were executed.");
    }
}