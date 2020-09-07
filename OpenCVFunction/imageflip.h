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

#include "CustomWidgets/baseconfigwidget.h"

class ImageFlip : public BaseConfigWidget
{
    Q_OBJECT
public:
    ImageFlip();
    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private slots:
    void imgFlipRadioButtonClicked(int flipFlagCode);

private:
    int flipFlagCode = 0;

    QVector<QPair<int, QString>> flipFlagsAll =
    {
        {-99, "No flip"},
        {0, "X axis"},
        {1, "Y axis"},
        {-1, "X and Y axis"}
    };

    void initWidget() override;
};
