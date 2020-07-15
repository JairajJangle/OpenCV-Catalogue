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

#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

class LabelledComboBox : public QHBoxLayout
{
    Q_OBJECT

private:
    QLabel* titleLabel = new QLabel();

public:
    QComboBox* comboBox = new QComboBox();

    explicit LabelledComboBox(QString title,
                              QList<QVariant> valueList,
                              int comboBoxFixedWidth = 0,
                              int labelFixedWidth = 0,
                              QWidget *parent = nullptr)
        :QHBoxLayout(parent)
    {
        for(auto& i : valueList)
        {
            comboBox->addItem(i.toString(), i);
        }

        initWidget(title, comboBoxFixedWidth, labelFixedWidth);
    }

    explicit LabelledComboBox(QString title,
                              QMap<QString, QVariant> nameValueMap,
                              int comboBoxFixedWidth = 0,
                              int labelFixedWidth = 0,
                              QWidget *parent = nullptr)
        :QHBoxLayout(parent)
    {
        QMapIterator<QString, QVariant> i(nameValueMap);
        while (i.hasNext())
        {
            i.next();
            comboBox->addItem(i.key(), i.value());
        }
        initWidget(title, comboBoxFixedWidth, labelFixedWidth);
    }

    void initWidget(QString title,
                    int comboBoxFixedWidth = 0,
                    int labelFixedWidth = 0)
    {
        if(labelFixedWidth != 0)
            titleLabel->setFixedWidth(labelFixedWidth);

        titleLabel->setText(title);

        if(comboBoxFixedWidth != 0)
            comboBox->setFixedWidth(comboBoxFixedWidth);

        this->addWidget(titleLabel);

        this->addStretch();
        this->addWidget(comboBox);
        this->addStretch();

        // TODO: Use Lambda SIGNAL SLOT instead
        connect(comboBox, SIGNAL(currentIndexChanged(int)),
                this, SLOT(indexChanged(int)));
    }

    virtual ~LabelledComboBox() {};

signals:
    void currentIndexChanged(QVariant);

private slots:
    void indexChanged(int index){
        emit currentIndexChanged(comboBox->itemData(index));
    }
};

