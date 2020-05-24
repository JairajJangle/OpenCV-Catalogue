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

#ifndef ERRORLABEL_H
#define ERRORLABEL_H

#include <QLabel>

class ErrorLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ErrorLabel(QString error = "", QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags())
    {
        this->setStyleSheet("QLabel { color : red; }");
        this->setText(error);
        QSizePolicy sp_retain = this->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        this->setSizePolicy(sp_retain);
    }
    void hide()
    {
        this->setVisible(false);
    }
    void show()
    {
        this->setVisible(true);
    }
    ~ErrorLabel()
    {

    }
};

#endif // ERRORLABEL_H
