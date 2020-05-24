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

#ifndef SLIDERLAYOUT_H
#define SLIDERLAYOUT_H

#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>

class SliderLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    QLabel* titleLabel  = new QLabel();
    QLabel* valueLabel  = new QLabel();
    QSlider* slider = new QSlider();

    explicit SliderLayout(QString title,
                          int initialValue,
                          int minValue = 0,
                          int maxValue = 100,
                          int fixedWidth = 160,
                          int fixedHeight = 60,
                          QWidget* parent = Q_NULLPTR,
                          Qt::WindowFlags f = Qt::WindowFlags())
    {
        QSizePolicy sp_retainTitle = titleLabel->sizePolicy();
        sp_retainTitle.setRetainSizeWhenHidden(true);
        titleLabel->setSizePolicy(sp_retainTitle);
        QSizePolicy sp_retainValue = valueLabel->sizePolicy();
        sp_retainValue.setRetainSizeWhenHidden(true);
        valueLabel->setSizePolicy(sp_retainValue);
        QSizePolicy sp_retainSlider = slider->sizePolicy();
        sp_retainSlider.setRetainSizeWhenHidden(true);
        slider->setSizePolicy(sp_retainSlider);

        this->setSpacing(15);

        slider->setFixedSize(fixedWidth, fixedHeight);
        slider->setSingleStep(20);
        slider->setOrientation(Qt::Horizontal);
        slider->setRange(minValue, maxValue);
        slider->setValue(initialValue);

        titleLabel->setText(title);
        valueLabel->setText(QString::number(initialValue));
        valueLabel->setFixedSize(40, 20);

        this->addWidget(titleLabel);
        this->addWidget(slider);
        this->addWidget(valueLabel);

        connect(slider, SIGNAL(valueChanged(int)),this,
                SLOT(valueChanged(int)));
        connect(slider, &QSlider::valueChanged, this,
                [=]() {
            emit sliderValueChanged(slider->value());
        });
    }

    void setVisible(bool visible)
    {
        titleLabel->setVisible(visible);
        valueLabel->setVisible(visible);
        slider->setVisible(visible);
    }

    virtual ~SliderLayout() {};

signals:
    void sliderValueChanged(int);

private slots:
    void valueChanged(int value){
        valueLabel->setText(QString::number(value));
    }
};

#endif // SLIDERLAYOUT_H
