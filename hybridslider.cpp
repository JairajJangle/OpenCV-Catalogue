#include "hybridslider.h"
#include "ui_hybridslider.h"

HybridSlider::HybridSlider(QWidget *parent,
                           int initVal,
                           int rangeMin,
                           int rangeMax) :
    QWidget(parent),
    ui(new Ui::HybridSlider)
{
    ui->setupUi(this);

    ui->lineEditMinVal->setValidator(new QIntValidator());
    ui->lineEditMaxVal->setValidator(new QIntValidator());
    ui->editValue->setValidator(new QIntValidator());

    ui->sliderVal->setValue(initVal);
    valueChanged(initVal);
    ui->sliderVal->setMinimum(rangeMin);
    ui->lineEditMinVal->setText(QString::number(rangeMin));
    ui->sliderVal->setMaximum(rangeMax);
    ui->lineEditMaxVal->setText(QString::number(rangeMax));

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

    connect(ui->editValue, SIGNAL(focussed(bool)),
            this, SLOT(valLineEditFocusChanged(bool)));

    connect(ui->editValue, SIGNAL(textChanged(const QString&)),
            this, SLOT(valueChanged(const QString&)));
}

void HybridSlider::showRangeBox()
{
    bool rangeBoxVisibility = ui->lineEditMinVal->isVisible();

    if(currentMode == APPLIED)
    {
        ui->buttonEditApply->setText("Set Range");
        rangeBoxVisibility = true;
        currentMode = EDIT;
    }
    else if(ui->lineEditMinVal->text().toInt()
            < ui->lineEditMaxVal->text().toInt()) // if currentMode == EDIT
    {
        // TODO: Check validity
        // TODO: Apply Range values here
        ui->buttonEditApply->setText("Edit Range");
        rangeBoxVisibility = false;
        currentMode = APPLIED;

        ui->sliderVal->setMinimum(ui->lineEditMinVal->text().toInt());
        ui->sliderVal->setMaximum(ui->lineEditMaxVal->text().toInt());

        ui->labelMinVal->setText(ui->lineEditMinVal->text());
        ui->labelMaxVal->setText(ui->lineEditMaxVal->text());
    }

    setRangeBoxVisibility(rangeBoxVisibility);
}

void HybridSlider::valLineEditFocusChanged(bool isFocused)
{
    isLineEditFocused = isFocused;
}

void HybridSlider::valueChanged(int value)
{
    if(!isLineEditFocused)
        ui->editValue->setText(QString::number(value));
}

void HybridSlider::valueChanged(const QString& text)
{
    if(isLineEditFocused)
    {
        int value = text.toInt();

        int round = value % 100;
        int low = value - round;
        int high = low + 100;

        ui->sliderVal->setMinimum(low);
        ui->sliderVal->setMaximum(high);
        ui->labelMinVal->setText(QString::number(low));
        ui->labelMaxVal->setText(QString::number(high));

        ui->lineEditMinVal->setText(QString::number(low));
        ui->lineEditMaxVal->setText(QString::number(high));

        ui->sliderVal->setValue(value);
    }
}

void HybridSlider::setRangeBoxVisibility(bool visibility)
{
    ui->label_5->setVisible(visibility);
    ui->lineEditMinVal->setVisible(visibility);
    ui->label_6->setVisible(visibility);
    ui->lineEditMaxVal->setVisible(visibility);
}

HybridSlider::~HybridSlider()
{
    delete ui;
}
