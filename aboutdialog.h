#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();


private slots:
    void openLeadDevSite(const QString& url);
    void openPayPalDonatePage();
    void openLiberaPayDOnatePage();

private:
    const QString paypalDonateUrl = "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=PPXTF24LWH86U";
    const QString liberaPayUrl = "https://liberapay.com/FutureJJ/donate";

    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
