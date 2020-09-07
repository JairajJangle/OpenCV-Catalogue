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

class ApplyResetButtonLayout;
class LineEditLayout;

class HoughLines: public BaseConfigWidget
{
    Q_OBJECT
public:
    HoughLines();

    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private slots:
    void applyClicked();
    void resetClicked();

private:
    QVariant* rho = new QVariant(1); // double
    QVariant* theta = new QVariant(CV_PI/180); // double
    QVariant* threshold = new QVariant(50); // int
    QVariant* srn = new QVariant(50.0); // double
    QVariant* stn = new QVariant(10.0); // double

    LineEditLayout* rhoLineEditLayout;
    LineEditLayout* thetaLayout;
    LineEditLayout* thresholdLayout;
    LineEditLayout* srnLayout;
    LineEditLayout* stnLayout;

    QVector<QPair<LineEditLayout*, QVariant*>> lineEditsWithParams;

    ApplyResetButtonLayout* applyResetBox;

    void initWidget() override;
};
