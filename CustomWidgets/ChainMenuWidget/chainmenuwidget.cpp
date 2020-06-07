#include "chainmenuwidget.h"
#include "ui_chainmenuwidget.h"
//#include <QDebug>

ChainMenuWidget::ChainMenuWidget(QWidget *parent) :
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

//    connect(ui->comboBox, SIGNAL(activated(int)),
//            this, SLOT(operationChangedSlot(int)));
}

//void ChainMenuWidget::operationChangedSlot(int index)
//{
//    qDebug() << "Current Combo Box = " << index;
//    emit operationChangedSignal(index);
//}

void ChainMenuWidget::setAddButonEnabled(bool enabled)
{
    ui->buttonAdd->setEnabled(enabled);
}
void ChainMenuWidget::setRemoveButtonEnabled(bool enabled)
{
    ui->buttonRemove->setEnabled(enabled);
}
void ChainMenuWidget::setComboBoxEnabled(bool enabled)
{
    ui->comboBox->setEnabled(enabled);
}
void ChainMenuWidget::setEnabled(bool enabled)
{
    setAddButonEnabled(enabled);
    setRemoveButtonEnabled(enabled);
    setComboBoxEnabled(enabled);
}
void ChainMenuWidget::setCurrentOperation(QString operationName)
{
    ui->comboBox->setCurrentText(operationName);
}

ChainMenuWidget::~ChainMenuWidget()
{
    delete ui;
}
