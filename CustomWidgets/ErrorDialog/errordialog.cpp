#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);

    connect(ui->buttonOK, SIGNAL(released()),
            this, SLOT(hideDialog()));
}

void ErrorDialog::setText(QString title, QString details)
{
    ui->labelSummary->setText(title);
    ui->textDetail->setText(details);
}

QString ErrorDialog::getDetails()
{
    return ui->textDetail->toPlainText();
}

void ErrorDialog::hideDialog()
{
    this->hide();
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}
