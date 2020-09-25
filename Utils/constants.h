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
/**
 * @brief appName Application name
 */
[[maybe_unused]] static const char* appName = "OpenCV Catalogue";

/**
 * @brief version Application version name
 */
[[maybe_unused]] static const char* version = "v0.3.2";
}

/**
 * @namespace RegExps Holds all Regexes to be used by OpenCV Catalogue
 */
namespace RegExps {

/**
 * @brief onlyDigits Regex to filter our only integer values
 */
[[maybe_unused]] static const char* onlyDigits = "\\d*";

/**
 * @brief decimal0To1 Regex to filter decimal values between 0 to 1 with precision = 4
 */
[[maybe_unused]] static const char* decimal0To1 = "^(0(\\.[0-9]{1,4})?|1(\\.0{1,4})?)$";
}

/**
 * @namespace Strings Holds all constant stirng values to be used by OpenCV Catalogue
 *
 * Note that, these strings exclude above defined strings
 */
namespace Strings {
[[maybe_unused]] static const char* dark = "dark";
[[maybe_unused]] static const char* light = "light";
[[maybe_unused]] static const char* noOperationSelected = "No operation Selected";
[[maybe_unused]] static const char* fps = "FPS: %1";
}
