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
#include <QPushButton>

class ApplyResetButtonLayout : public QHBoxLayout
{
    Q_OBJECT

    QPushButton* applyButton = new QPushButton("Apply");
    QPushButton* resetButton = new QPushButton("Reset");

public:
    explicit ApplyResetButtonLayout(bool resetVisible = true,
                                    bool applyVisible = true,
                                    QWidget* parent = nullptr)
        : QHBoxLayout(parent){
        this->setAlignment(Qt::AlignHCenter);
        this->addWidget(applyButton);
        this->addWidget(resetButton);

        resetButton->setVisible(resetVisible);
        applyButton->setVisible(applyVisible);

        connect(applyButton, &QPushButton::released, this,
                [=]() {
            emit applyClicked();
        });

        connect(resetButton, &QPushButton::released, this,
                [=]() {
            emit resetClicked();
        });
    }

signals:
    void applyClicked();
    void resetClicked();
};
