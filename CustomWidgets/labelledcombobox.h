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

#pragma once

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QMap>

class LabelledComboBox : public QHBoxLayout
{
    Q_OBJECT

private:
    QLabel* titleLabel = new QLabel();

public:
    QComboBox* comboBox = new QComboBox();

    explicit LabelledComboBox(QString title,
                              QMap<QString, QVariant> nameValueMap,
                              int comboBoxFixedWidth = 0,
                              int labelFixedWidth = 0,
                              QWidget *parent = nullptr)
        :QHBoxLayout(parent)
    {
        titleLabel->setText(title);
        if(labelFixedWidth != 0)
            titleLabel->setFixedWidth(labelFixedWidth);

        QMapIterator<QString, QVariant> i(nameValueMap);
        while (i.hasNext())
        {
            i.next();
            comboBox->addItem(i.key(), i.value());
        }

        if(comboBoxFixedWidth != 0)
            comboBox->setFixedWidth(comboBoxFixedWidth);

        this->addWidget(titleLabel);

        this->addStretch();
        this->addWidget(comboBox);
        this->addStretch();
    }

private slots:
    void imgFlipRadioButtonClicked(int flipFlagCode){
    }
};

