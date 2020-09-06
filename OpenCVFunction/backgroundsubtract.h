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

class BackgroundSubtraction : public BaseConfigWidget
{
    Q_OBJECT
public:
    BackgroundSubtraction();
    cv::Mat getProcessedImage(cv::Mat inputImage) override;

private slots:
    void bkgSubTechChanged(int bkgSubTech);
    void resetAnchorClicked();

private:
    void initWidget() override;

    QList<cv::Ptr< cv::BackgroundSubtractor>> bkgSubTechList;

    // More at: https://docs.opencv.org/3.4/d7/df6/classcv_1_1BackgroundSubtractor.html
    QList<QString> bkgSubTechs = { "KNN", "MOG", "MOG2", "GMG", "GSOC", "CNT", "LSBP" };

    int selectedTech = 0; // KNN
    double learningRate = 0.1;
};
