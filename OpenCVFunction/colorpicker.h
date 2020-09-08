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
    ColorPicker()
    {
        operationName = "Color Picker";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat-at";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        cv::Mat outputImage;

        // If No Location is selected: o/p = 0
        if(begin ==cv::Point(-1, -1))
            return inputImage;

        QString locationValues =
                QString::number(begin.x) + ", "
                +  QString::number(begin.y);

        locLineEditLayout->setText(locationValues);

        cv::Vec3b color = inputImage.at<cv::Vec3b>(begin);

        QString rgbValues =
                QString::number(color[0]) + ", "
                +  QString::number(color[1]) + ", "
                +  QString::number(color[2]);

        rgbLineEditLayout->setText(rgbValues);


        begin =cv::Point(-1, -1);

        return inputImage;
    }
    catch(cv::Exception& e){
        throw e;
    } catch(std::exception& e) {
        throw e;
    }
    catch(...){
    throw std::string("Unknown Exception in ")
    + std::string(typeid(this).name());
}

private:
LineEditLayout* rgbLineEditLayout = new LineEditLayout("RGB", "000, 000, 000", 200);
LineEditLayout* locLineEditLayout = new LineEditLayout("Location", "No location selected", 200);

QLabel* infoLabel  = new QLabel("Click on Output feed to pick color\n");

void initWidget() override
{
    locLineEditLayout->lineEdit->setReadOnly(true);
    vBoxSub->addWidget(infoLabel);

    vBoxSub->addLayout(rgbLineEditLayout);
    vBoxSub->addLayout(locLineEditLayout);

    BaseConfigWidget::initWidget();
}
};
