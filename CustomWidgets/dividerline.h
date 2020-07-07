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


#ifndef HDIVIDERLINE_H
#define HDIVIDERLINE_H

#include <QFrame>

class DividerLine : public QFrame
{
public:

    explicit DividerLine(QWidget* parent = nullptr,
                         Qt::WindowFlags f = Qt::WindowFlags())
        : QFrame(parent)
    {
        this->setWindowFlags(f);
        this->setObjectName(QString::fromUtf8("line"));
        this->setGeometry(QRect(320, 150, 118, 3));
        this->setFrameShape(QFrame::HLine);
        this->setFrameShadow(QFrame::Sunken);
        this->setFixedHeight(20);
    }
};

#endif // HDIVIDERLINE_H
