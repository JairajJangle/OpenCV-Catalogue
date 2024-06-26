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

#include <QLineEdit>

/**
 * @brief The FocusAwareLineEdit class Custom widget to emit signal when there is
 *  focus change on this customized Line Edit widget
 */
class FocusAwareLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    FocusAwareLineEdit(QWidget *parent = 0);
    ~FocusAwareLineEdit();

signals:
    /**
     * @brief focussed Signal emitted when focus on this widget is changed
     * @param hasFocus True when this widget is in focus else false
     */
    void focussed(bool hasFocus);

protected:
    /*
     * See QLineEdit docs by QT
     */
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);
};
