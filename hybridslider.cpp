#include "hybridslider.h"
#include "ui_hybridslider.h"

HybridSlider::HybridSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HybridSlider)
{
    ui->setupUi(this);

    ui->buttonEditApply->setText("Edit Range");

    ui->label_5->setVisible(false);
    ui->lineEditMinVal->setVisible(false);
    ui->label_6->setVisible(false);
    ui->lineEditMaxVal->setVisible(false);

    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    connect(ui->buttonEditApply,SIGNAL(released()),this,SLOT(showRangeBox()));
}

void HybridSlider::showRangeBox()
{
    ui->label_5->setVisible(true);
    ui->lineEditMinVal->setVisible(true);
    ui->label_6->setVisible(true);
    ui->lineEditMaxVal->setVisible(true);

    ui->buttonEditApply->setText("Apply Range");
}

HybridSlider::~HybridSlider()
{
    delete ui;
}
