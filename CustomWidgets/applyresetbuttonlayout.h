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

/**
 * @brief The ApplyResetButtonLayout class Custom Layout consiting of Apply and Reset
 *  button in a Horizontal Box Layout.
 */
class ApplyResetButtonLayout : public QHBoxLayout
{
    Q_OBJECT

    /**
     * @brief applyButton Apply Push Button.
     */
    QPushButton* applyButton = new QPushButton("Apply");

    /**
     * @brief resetButton Reset Push Button
     */
    QPushButton* resetButton = new QPushButton("Reset");

public:
    /**
     * @brief ApplyResetButtonLayout Constructor for this class
     * @param resetVisible Set true to make reset button visible else false,
     *  default = true
     * @param applyVisible Set true to make apply button visible else false,
     *  default = true
     * @param parent Pass the parent widget, nullable optional parameter
     */
    explicit ApplyResetButtonLayout(bool resetVisible = true,
                                    bool applyVisible = true,
                                    QWidget* parent = nullptr)
        : QHBoxLayout(parent){
        this->setAlignment(Qt::AlignHCenter);
        this->addWidget(applyButton);
        this->addWidget(resetButton);

        resetButton->setVisible(resetVisible);
        applyButton->setVisible(applyVisible);

        /*
         * Lambda for connecting Apply button click event with the corresponding signal
         */
        connect(applyButton, &QPushButton::released, this,
                [=]() {
            emit applyClicked();
        });

        /*
         * Lambda for connecting Reset button click event with the corresponding signal
         */
        connect(resetButton, &QPushButton::released, this,
                [=]() {
            emit resetClicked();
        });
    }

signals:
    /**
     * @brief applyClicked Signal emitted when Apply button is clicked
     */
    void applyClicked();
    /**
     * @brief resetClicked Signal emitted when Reset button is clicked
     */
    void resetClicked();
};
