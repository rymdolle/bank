#ifndef DASHBOARDWINDOW_HPP
#define DASHBOARDWINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include "user.hpp"

class TransferWindow;
class HistoryWindow;
class CreateAccountWindow;
class ChangePasswordWindow;
class DepositWindow;
class InterestWindow;
class WithdrawWindow;
class ProfileWindow;
class LoanWindow;
class ChartWindow;
class NotificationWindow;
class RecurringTransferWindow;
class BudgetWindow;
class SupportWindow;
class SettingsWindow;
class BackupWindow;
class RestoreWindow;
class HelpWindow;

class DashboardWindow : public QWidget {
    Q_OBJECT

public:
    explicit DashboardWindow(const User &user, QWidget *parent = nullptr);
    ~DashboardWindow();

signals:
    void logout();

private slots:
    void onTransferClicked();
    void onHistoryClicked();
    void onTransferSuccess(int srcId, int dstId, int amount);
    void onLogoutClicked();
    void onDeleteAccountClicked();
    void onCreateAccountClicked();
    void onAccountCreated(const Account &account);
    void onChangePasswordClicked();
    void onDepositClicked();
    void onDepositSuccess(int accountId, int amount);
    void onInterestClicked();
    void onInterestApplied(int accountId, int amount);
    void onWithdrawClicked();
    void onWithdrawSuccess(int accountId, int amount);
    void onProfileClicked();
    void onNameChanged(const std::string &newName);
    void onLoanClicked();
    void onLoanApproved(int accountId, int amount);
    void onChartClicked();
    void onNotificationsClicked();
    void onRecurringTransferClicked();
    void onBudgetClicked();
    void onSupportClicked();
    void onDarkModeClicked();
    void onSettingsClicked();
    void onBackupClicked();
    void onRestoreClicked();
    void onExportAccountsClicked();
    void onHelpClicked();

private:
    void processRecurringTransfers();
    void refreshAccountList();
    User user_;
    QLabel *welcomeLabel;
    QListWidget *accountsList;
    TransferWindow *transferWindow = nullptr;
    HistoryWindow *historyWindow = nullptr;
    CreateAccountWindow *createAccountWindow = nullptr;
    ChangePasswordWindow *changePasswordWindow = nullptr;
    DepositWindow *depositWindow = nullptr;
    InterestWindow *interestWindow = nullptr;
    WithdrawWindow *withdrawWindow = nullptr;
    ProfileWindow *profileWindow = nullptr;
    LoanWindow *loanWindow = nullptr;
    ChartWindow *chartWindow = nullptr;
    NotificationWindow *notificationWindow = nullptr;
    RecurringTransferWindow *recurringTransferWindow = nullptr;
    BudgetWindow *budgetWindow = nullptr;
    bool isDarkMode = false;
    SupportWindow *supportWindow = nullptr;
    SettingsWindow *settingsWindow = nullptr;
    BackupWindow *backupWindow = nullptr;
    RestoreWindow *restoreWindow = nullptr;
    HelpWindow *helpWindow = nullptr;
};

#endif // DASHBOARDWINDOW_HPP