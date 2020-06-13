#include "chainmenuwidget.h"
#include "ui_chainmenuwidget.h"
#include <QComboBox>
//#include <QDebug>

ChainMenuWidget::ChainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChainMenuWidget)
{
    ui->setupUi(this);

    ui->verticalLayout_2->setAlignment(Qt::AlignCenter);

    for(QPair<int, QString> chainMenuItem : chainMenuOpList)
    {
        ui->comboBox->addItem(chainMenuItem.second, chainMenuItem.first);
    }

    connect(ui->buttonAdd, &QToolButton::released,this,
            [=](){
        emit addOperationClicked();
    });

    connect(ui->buttonRemove, &QToolButton::released,this,
            [=](){
        emit removeOperationClicked();
    });

    connect(ui->comboBox, qOverload<int>(&QComboBox::activated), this,
            [=](int index){
        emit operationChanged(index);
    });

    connect(ui->radioButton, &QRadioButton::clicked, this,
            [=]() {
        emit radioButtonChecked();
    });
}

QRadioButton* ChainMenuWidget::getRadioButton()
{
    return ui->radioButton;
}

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
