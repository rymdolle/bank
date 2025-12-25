#ifndef TWOFACTORWINDOW_HPP
#define TWOFACTORWINDOW_HPP

#include <QWidget>
#include <QLineEdit>
#include <QString>

class TwoFactorWindow : public QWidget {
    Q_OBJECT
public:
    explicit TwoFactorWindow(QWidget *parent = nullptr);

signals:
    void verificationSuccessful();
    void canceled();

private slots:
    void onVerifyClicked();
    void onCancelClicked();

private:
    QLineEdit *codeInput;
    QString generatedCode;
};

#endif // TWOFACTORWINDOW_HPP