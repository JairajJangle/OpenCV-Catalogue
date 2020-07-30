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

#include <QFrame>

/**
 * @brief DividerLine Custom QFrame class to draw horizontal line/divider
 */
class DividerLine : public QFrame
{
public:

    /**
     * @brief DividerLine Constructor for Divider Line Custom Widget
     * @param fixedHeight Set Fixed Height of the Divider Line
     * @param parent Set parent of Divider Line widget, nullable optional parameter
     * @param f Optional Window Flag
     */
    explicit DividerLine(int fixedHeight = 0,
                         QWidget* parent = nullptr,
                         Qt::WindowFlags f = Qt::WindowFlags())
        : QFrame(parent)
    {
        this->setWindowFlags(f);
        this->setObjectName(QString::fromUtf8("line"));
        this->setGeometry(QRect(320, 150, 118, 3));
        this->setFrameShape(QFrame::HLine);
        this->setFrameShadow(QFrame::Sunken);
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        this->setFixedHeight(fixedHeight == 0 ? 20 : fixedHeight);
    }
};
