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

#ifndef UTILS_H
#define UTILS_H

#include <cmath>

#include <QList>

namespace Numeric {
// extern:
double setPrecision(double number, int decimalPlaces);
// inline:
inline double setPrecision(double number, int decimalPlaces)
{
    int n = (int)(number *pow(10, decimalPlaces));
    return ((double)n) / pow(10, decimalPlaces);
}
}

inline QList<QPair<int, QString>> chainMenuOpList;

#define GET_VARIABLE_NAME(Variable) (#Variable)

#endif // UTILS_H
