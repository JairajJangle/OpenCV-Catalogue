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

class LineEditLayout;
class ApplyResetButtonLayout;

class HoughCircles: public BaseConfigWidget
{
    Q_OBJECT
public:
    HoughCircles();

    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private slots:
    void applyClicked();
    void resetClicked();

private:

    QVariant* dp = new QVariant(1);
    QVariant* minDist = new QVariant(-1.0);
    QVariant* param1 = new QVariant(200.0);
    QVariant* param2 = new QVariant(100.0);
    QVariant* minRadius = new QVariant(0);
    QVariant* maxRadius = new QVariant(0);

    LineEditLayout* dpLineEditLayout;
    LineEditLayout* minDistLayout;
    LineEditLayout* param1Layout;
    LineEditLayout* param2Layout;
    LineEditLayout* minRadiusLayout;
    LineEditLayout* maxRadiusLayout;

    QVector<QPair<LineEditLayout*, QVariant*>> lineEditsWithParams;

    ApplyResetButtonLayout* applyResetBox;

    void initWidget() override;
};
