#include "chainmenuwidget.h"
#include "ui_chainmenuwidget.h"

ChainMenuWidget::ChainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChainMenuWidget)
{
    ui->setupUi(this);
}

ChainMenuWidget::~ChainMenuWidget()
{
    delete ui;
}
