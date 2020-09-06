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

class ColorSpace : public BaseConfigWidget
{
    Q_OBJECT
public:
    ColorSpace();

    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private slots:
    void colorConvRadioButtonClicked(int colorConvCode);

private:
    QVector<QPair<int, QString>> colorCodesAll =
    {
        {-1, "RGB"},
        {cv::COLOR_BGR2HSV, "HSV"},
        {cv::COLOR_BGR2GRAY, "Grayscale"},
        {cv::COLOR_BGR2Lab, "LAB"},
        {cv::COLOR_BGR2YCrCb, "YCrCb"},
        {cv::COLOR_BGR2Luv, "Luv"},
        {cv::COLOR_BGR2HLS, "HLS"},
        {cv::COLOR_BGR2XYZ, "XYZ"},
        {cv::COLOR_BGR2YUV, "YUV"}
    };

    int colorConvCode = 0;

protected:
    void initWidget() override;
};
