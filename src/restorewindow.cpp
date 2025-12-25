#include "restorewindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDir>

RestoreWindow::RestoreWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setWindowTitle("Restore Database");

    layout->addWidget(new QLabel("Restore data from a zip backup.\nWarning: This will overwrite current data!", this));

    QPushButton *restoreBtn = new QPushButton("Select Backup & Restore", this);
    layout->addWidget(restoreBtn);
    connect(restoreBtn, &QPushButton::clicked, this, &RestoreWindow::onRestoreClicked);

    resize(300, 150);
}

void RestoreWindow::onRestoreClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Select Backup", "", "Zip Files (*.zip)");
    if (fileName.isEmpty()) return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Restore", "This will overwrite all current data. Are you sure?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) return;

    QProcess unzipProcess;
    QString program = "unzip";
    QStringList arguments;
    arguments << "-o" << fileName << "-d" << "data/";

    unzipProcess.start(program, arguments);
    if (!unzipProcess.waitForStarted() || !unzipProcess.waitForFinished()) {
         QMessageBox::warning(this, "Error", "Failed to run unzip command. Please ensure 'unzip' is installed.");
         return;
    }

    if (unzipProcess.exitCode() == 0) {
        QMessageBox::information(this, "Success", "Database restored successfully! Please restart the application.");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Unzip command failed.\n" + unzipProcess.readAllStandardError());
    }
}