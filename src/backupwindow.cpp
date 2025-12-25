#include "backupwindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QFile>

BackupWindow::BackupWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Backup Database");

    layout->addWidget(new QLabel("Create a zip backup of your data files.", this));

    QPushButton *backupBtn = new QPushButton("Select Destination & Backup", this);
    layout->addWidget(backupBtn);
    connect(backupBtn, &QPushButton::clicked, this, &BackupWindow::onBackupClicked);

    resize(300, 150);
}

void BackupWindow::onBackupClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Backup", "backup.zip", "Zip Files (*.zip)");
    if (fileName.isEmpty()) return;

    // List of files to backup
    QStringList files;
    files << "data/users.txt" << "data/accounts.txt" << "data/transactions.txt" 
          << "data/notifications.txt" << "data/recurring_transfers.txt" 
          << "data/budgets.txt" << "data/support_messages.txt" << "data/security.txt";

    // Check if files exist
    QStringList existingFiles;
    for (const QString &f : files) {
        if (QFile::exists(f)) existingFiles << f;
    }

    if (existingFiles.isEmpty()) {
        QMessageBox::warning(this, "Error", "No data files found to backup.");
        return;
    }

    QProcess zipProcess;
    QString program = "zip";
    QStringList arguments;
    arguments << "-j" << fileName; // -j to junk paths (flat structure in zip)
    arguments << existingFiles;

    zipProcess.start(program, arguments);
    if (!zipProcess.waitForStarted() || !zipProcess.waitForFinished()) {
         QMessageBox::warning(this, "Error", "Failed to run zip command. Please ensure 'zip' is installed.");
         return;
    }

    if (zipProcess.exitCode() == 0) {
        QMessageBox::information(this, "Success", "Backup created successfully!");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Zip command failed.\n" + zipProcess.readAllStandardError());
    }
}