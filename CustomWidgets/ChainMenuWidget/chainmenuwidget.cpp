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

    for(auto key : chainMenuOpMap.keys())
    {
        ui->comboBox->addItem(chainMenuOpMap.value(key), key);
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

void ChainMenuWidget::setLineVisibility(bool visible)
{
    ui->line->setVisible(visible);
}

void ChainMenuWidget::setStyleSheet(bool isDarkMode)
{
    ui->buttonAdd->setStyleSheet(isDarkMode ? buttonAddDarkStyle
                                         : buttonAddLightStyle);
    ui->buttonRemove->setStyleSheet(isDarkMode ? buttonRemoveDarkStyle
                                         : buttonRemoveLightStyle);
}

ChainMenuWidget::~ChainMenuWidget()
{
    delete ui;
}
