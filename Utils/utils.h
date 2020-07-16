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

#include <cmath>

#include <QMap>
#include <QPoint>
#include <QWidget>

namespace Numeric {
/**
 * setPrecision(...) to set decimal precision of
 * @param number double by @param decimalPlaces
 */
// extern:
double setPrecision(double number, int decimalPlaces);
// inline:
inline double setPrecision(double number, int decimalPlaces)
{
    int n = (int)(number *pow(10, decimalPlaces));
    return ((double)n) / pow(10, decimalPlaces);
}
}

/**
 * @brief chainMenuOpMap
 *
 * Stores map of MainWindow::OpCodes as OpenCV operation codes and
 * name of the operation in QString
 */
inline QMap<int, QString> chainMenuOpMap;

/**
 * @brief isDarkModeOn
 *
 * Stores the theme mode OpenCV Catalogue is in
 * This value can be accessed by all widgets to switch their style sheets
 * if necessary.
 *
 * Generally, BaseConfigWidget have changeWidgetsStyleSheet(...) exposed
 * when called, it should invoke the style sheet change of all children widgets
 * whether they are derived or members of derived classes
 */
inline bool isDarkModeOn = true;

namespace WidgetUtils {
QPoint getWidgetCenter(QWidget* widget);
inline QPoint getWidgetCenter(QWidget* widget)
{
    QPoint position = QPoint(0,0);
    position.setX(widget->geometry().x() + widget->geometry().width()/2);
    position.setY(widget->geometry().y() + widget->geometry().height()/2);
    return  position;
}
}

#define GET_VARIABLE_NAME(Variable) (#Variable)
