#include "hybridslider.h"
#include "ui_hybridslider.h"

HybridSlider::HybridSlider(QWidget *parent,
                           int initVal,
                           int rangeMin,
                           int rangeMax) :
    QWidget(parent),
    ui(new Ui::HybridSlider)
{
    this->initVal = initVal;
    this->rangeMin = rangeMin;
    this->rangeMax = rangeMax;

    ui->setupUi(this);

    ui->sliderVal->setValue(initVal);
    valueChanged(initVal);
    ui->sliderVal->setMinimum(rangeMin);
    ui->sliderVal->setMaximum(rangeMax);

    ui->buttonEditApply->setText("Edit Range");

    ui->label_5->setVisible(false);
    ui->lineEditMinVal->setVisible(false);
    ui->label_6->setVisible(false);
    ui->lineEditMaxVal->setVisible(false);

    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    connect(ui->sliderVal, SIGNAL(valueChanged(int)),
            this, SLOT(valueChanged(int)));
    connect(ui->buttonEditApply, &QPushButton::released, this,
            [=]() {
        if(currentMode == EDIT || currentMode == APPLIED)
            showRangeBox();
        emit editApplyClicked();
    });
}

void HybridSlider::showRangeBox()
{
    bool setRangeBoxVisibility;

    if(currentMode == APPLIED)
    {
        setRangeBoxVisibility = true;
        currentMode = EDIT;
    }
    else
    {
        setRangeBoxVisibility = false;
        currentMode = APPLIED;
        // TODO: Apply Range values here
    }

    ui->label_5->setVisible(setRangeBoxVisibility);
    ui->lineEditMinVal->setVisible(setRangeBoxVisibility);
    ui->label_6->setVisible(setRangeBoxVisibility);
    ui->lineEditMaxVal->setVisible(setRangeBoxVisibility);
}

void HybridSlider::applyValues()
{
    currentMode = APPLIED;
}

void HybridSlider::valueChanged(int value)
{
    ui->editValue->setText(QString::number(value));
}

HybridSlider::~HybridSlider()
{
    delete ui;
}
