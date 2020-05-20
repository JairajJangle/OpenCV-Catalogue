#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDesktopServices>
#include <QUrl>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->labelJairajJangle->setTextInteractionFlags(Qt::TextBrowserInteraction);

    ui->verticalLayout->setAlignment(Qt::AlignHCenter);

    connect(ui->labelJairajJangle,SIGNAL(linkActivated(const QString&)),this,SLOT(openURL(const QString&)));

    connect(ui->buttonContribute,SIGNAL(released()),this,SLOT(openGithubSourcePage()));
    connect(ui->buttonReportIssue,SIGNAL(released()),this,SLOT(openGithubIssuesPage()));

    connect(ui->buttonDonatePaypal, SIGNAL(released()), this, SLOT(openPayPalDonatePage()));
    connect(ui->buttonDonateLiberaPay, SIGNAL(released()), this, SLOT(openLiberaPayDOnatePage()));
}

void AboutDialog::openURL(const QString& link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void AboutDialog::openPayPalDonatePage()
{
    QDesktopServices::openUrl(QUrl(paypalDonateUrl));
}

void AboutDialog::openGithubSourcePage()
{
    QDesktopServices::openUrl(QUrl(githubSourceLink));
}

void AboutDialog::openGithubIssuesPage()
{
    QDesktopServices::openUrl(QUrl(githubIssuesLink));
}

void AboutDialog::openLiberaPayDOnatePage()
{
    QDesktopServices::openUrl(QUrl(liberaPayUrl));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
