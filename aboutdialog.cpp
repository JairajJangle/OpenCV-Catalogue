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

    connect(ui->labelJairajJangle,SIGNAL(linkActivated(const QString&)),this,SLOT(openLeadDevSite(const QString&)));
}

void AboutDialog::openLeadDevSite(const QString& link)
{
    QDesktopServices::openUrl(QUrl(link));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
