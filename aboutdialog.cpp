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

    connect(ui->buttonContribute, &QPushButton::released, this,
            [=]() {
        openURL(githubSourceLink);
    });
    connect(ui->buttonReportIssue, &QPushButton::released, this,
            [=]() {
        openURL(githubIssuesLink);
    });

    connect(ui->buttonDonatePaypal, &QPushButton::released, this,
            [=]() {
        openURL(paypalDonateUrl);
    });
    connect(ui->buttonDonateLiberaPay, &QPushButton::released, this,
            [=]() {
        openURL(liberaPayUrl);
    });
}

void AboutDialog::openURL(const QString& link)
{
    QDesktopServices::openUrl(QUrl(link));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
