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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QRegExp>

namespace Info {
    const QString appName = "OpenCV Catalogue";
    const QString version = "v0.2.1";
}

namespace RegExps {
     const QRegExp regEx0_1Decimal = QRegExp("^(0(\\.[0-9]{1,4})?|1(\\.0{1,4})?)$");
}

#define GET_VARIABLE_NAME(Variable) (#Variable)

#endif // CONSTANTS_H
