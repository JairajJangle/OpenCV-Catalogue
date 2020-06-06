#include "chainmenuwidget.h"
#include "ui_chainmenuwidget.h"

ChainMenuWidget::ChainMenuWidget(QWidget *parent,
                                 QList<QPair<int, QString>> chainMenuOpList) :
    QWidget(parent),
    ui(new Ui::ChainMenuWidget)
{
    ui->setupUi(this);

    for(QPair<int, QString> chainMenuItem : chainMenuOpList)
    {
        ui->comboBox->addItem(chainMenuItem.second, chainMenuItem.first);
    }

    connect(ui->buttonAdd, &QPushButton::released,this,
            [=](){
        emit addOperationClicked();
    });

    connect(ui->buttonRemove, &QPushButton::released,this,
            [=](){
        emit removeOperationClicked();
    });
}

void ChainMenuWidget::setAddButonEnabled(bool enabled)
{
    ui->buttonAdd->setEnabled(enabled);
}
void ChainMenuWidget::setRemoveButtonEnabled(bool enabled)
{
    ui->buttonRemove->setEnabled(enabled);
}

ChainMenuWidget::~ChainMenuWidget()
{
    delete ui;
}
