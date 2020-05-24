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

#ifndef COLORPICKER_H
#define COLORPICKER_H

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/lineeditlayout.h"
#include "Utils/baseconfigwidget.h"

class ColorPicker : public QWidget, public BaseConfigWidget
{
    Q_OBJECT
public:
    ColorPicker()
    {
        operationName = "Color Picker";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat-at";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat outputImage;

        // If No Location is selected: o/p = 0
        if(begin ==cv::Point(-1, -1))
            return inputImage;
        else
        {
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
        }

        begin =cv::Point(-1, -1);

        return inputImage;
    }

    ~ColorPicker()
    {
        printf("Color Picker destroyed\n");
    }

private:
    LineEditLayout* rgbLineEditLayout = new LineEditLayout("RGB", "000, 000, 000", 200);

    LineEditLayout* locLineEditLayout = new LineEditLayout("Location", "No location selected", 200);

    QLabel* infoLabel  = new QLabel("Click on Output feed to pick color\n");

    void initWidget()
    {
        locLineEditLayout->lineEdit->setReadOnly(true);
        vBoxSub->addWidget(infoLabel);

        vBoxSub->addLayout(rgbLineEditLayout);
        vBoxSub->addLayout(locLineEditLayout);

        BaseConfigWidget::initWidget();
    }
};


#endif // COLORPICKER_H
