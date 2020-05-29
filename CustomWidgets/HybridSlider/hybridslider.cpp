/* OpenCV Catalogue is a desktop GUI application to showcase some OpenCV functions
 * and parameter adjustment using controls in GUI.
 * Copyright (C) 2020  Jairaj Jangle
 *
 * This file is part of OpenCV Catalogue.
 *
 * OpenCV Catalogue is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenCV Catalogue is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenCV Catalogue.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "hybridslider.h"
#include "ui_hybridslider.h"

#include <QIntValidator>

HybridSlider::HybridSlider(QWidget *parent,
                           QString title,
                           int initVal,
                           int rangeMin,
                           int rangeMax) :
    QWidget(parent),
    ui(new Ui::HybridSlider)
{
    ui->setupUi(this);

    ui->labelTitle->setText(title);

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

    setRangeBoxVisibility(false);

    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    connect(ui->sliderVal, SIGNAL(valueChanged(int)),
            this, SLOT(valueChanged(int)));
    connect(ui->buttonEditApply, &QPushButton::released, this,
            [=]() {
        showRangeBox();
        /*
         * Connect this signal to slot which performs
         * adjustSize() on parent layout
         * example: wgtMain->adjustSize();
         * Reason: To refresh layout on visibility change of
         * Range Edit layout box
         */
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

    // FIXME: Hiding Range Box retains widget height

    //    if(rangeBoxVisibility)
    //        ui->verticalLayout->removeItem(ui->verticalSpacer);
    //    else
    //        ui->verticalLayout->removeItem(ui->verticalSpacer);
    //111 147

    //    if(!rangeBoxVisibility)
    //        ui->gridLayout->removeItem(ui->horizontalLayout_4);
    //    else
    //        ui->gridLayout->addLayout(ui->horizontalLayout_4, 1, 0);
    //    ui->gridLayout->update();
    //    ui->horizontalLayout_4->update();
    //    this->adjustSize();
}

void HybridSlider::valLineEditFocusChanged(bool isFocused)
{
    isLineEditFocused = isFocused;
}

void HybridSlider::valueChanged(int value)
{
    if(!isLineEditFocused)
        ui->editValue->setText(QString::number(value));

    emit sliderValueChanged(value);
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
