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
#include <QPushButton>

#include "CustomWidgets/baseconfigwidget.h"

class DualLineEditLayout;
class LineEditLayout;
class ErrorLabel;

class Blur : public BaseConfigWidget
{
    Q_OBJECT
public:
    Blur();

    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private slots:
    void applyKernelClicked();
    void resetAnchorClicked();

private:
    void initWidget() override;

    cv::Size kSize = cv::Size(101, 101);
    const int lineEditW = 50;

    DualLineEditLayout *kSizeDLEL;
    LineEditLayout* anchorLineEditLayout;

    QPushButton* applyButton = new QPushButton("Apply Kernel");
    QPushButton* resetAnchorButton = new QPushButton("Reset Anchor Position");
    ErrorLabel* errorLabel;
    QString prevAnchorText = "";
};
