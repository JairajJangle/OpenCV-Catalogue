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

class DualLineEditLayout;
class LineEditLayout;
class ApplyResetButtonLayout;

class ErodeDilate : public BaseConfigWidget
{
    Q_OBJECT
public:
    enum MorphologyType{ERODE, DILATE};
    ErodeDilate(MorphologyType morphologyType);

    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private slots:
    void applyClicked();
    void resetClicked();
    void morphShapeChanged(QVariant value);
    void iterationChanged(int value);
    void borderChanged(QVariant value);

private:
    const int dilationSize = 6;
    int kernelMorphShape = cv::MORPH_CROSS; // cv::MorphShapes
    cv::Size kSize = cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1);
    cv::Point kernelAnchor = cv::Point(-1, -1);
    int iterationCount = 1;
    int borderType = cv::BORDER_CONSTANT;
    const MorphologyType morphType;

    DualLineEditLayout* kSizeDLEL;

    LineEditLayout* anchorLineEditLayout;

    QString prevAnchorText = "";

    ApplyResetButtonLayout* applyResetBL;

    void initWidget() override;
};
