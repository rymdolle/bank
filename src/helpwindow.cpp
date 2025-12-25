#include "helpwindow.hpp"
#include <QVBoxLayout>

HelpWindow::HelpWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("User Manual");

    textBrowser = new QTextBrowser(this);
    textBrowser->setHtml(
        "<h1>Bank System User Manual</h1>"
        "<p>Welcome to the Bank System application. Here is a guide to the features:</p>"
        "<ul>"
        "<li><b>Transfer Money:</b> Send money between your accounts or to other users.</li>"
        "<li><b>Deposit/Withdraw:</b> Add or remove funds from your accounts.</li>"
        "<li><b>History:</b> View your transaction history, filter by date, and export to CSV.</li>"
        "<li><b>Charts:</b> Visualize your balance history over time.</li>"
        "<li><b>Budget:</b> Set monthly spending limits for your accounts.</li>"
        "<li><b>Recurring Transfers:</b> Schedule transfers to happen automatically.</li>"
        "<li><b>Loan:</b> Request a loan from the bank.</li>"
        "<li><b>Settings:</b> Change the application theme.</li>"
        "<li><b>Backup/Restore:</b> Save your data to a zip file or restore from one.</li>"
        "</ul>"
        "<p>For further assistance, use the 'Contact Support' button.</p>"
    );
    layout->addWidget(textBrowser);

    resize(500, 400);
}