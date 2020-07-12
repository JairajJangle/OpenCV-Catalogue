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

namespace Info {
[[maybe_unused]] static const char* appName = "OpenCV Catalogue";
[[maybe_unused]] static const char* version = "v0.2.1";
}

namespace RegExps {
[[maybe_unused]] static const char* onlyDigits = "\\d*";
[[maybe_unused]] static const char* decimal0To1 = "^(0(\\.[0-9]{1,4})?|1(\\.0{1,4})?)$";
}

namespace Strings {
[[maybe_unused]] static const char* noOperationSelected = "No operation Selected";
}
