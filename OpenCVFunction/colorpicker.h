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

// QT libs
#include <QLabel>

#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/baseconfigwidget.h"

class ColorPicker : public BaseConfigWidget
{
    Q_OBJECT
public:
    ColorPicker();

    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private:
    LineEditLayout* rgbLineEditLayout = new LineEditLayout("RGB", "000, 000, 000", 200);
    LineEditLayout* locLineEditLayout = new LineEditLayout("Location", "No location selected", 200);

    QLabel* infoLabel  = new QLabel("Click on Output feed to pick color\n");

    void initWidget() override;
};
