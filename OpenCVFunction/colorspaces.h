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
#include <QRadioButton>

#include "CustomWidgets/baseconfigwidget.h"

class ColorSpace : public BaseConfigWidget
{
    Q_OBJECT
public:
    ColorSpace()
    {
        operationName = "Color Space Conversion";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html#cvtcolor";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        cv::Mat outputImage;
        int selectedColorCode = colorCodesAll.at(colorConvCode).first;

        // If RGB is selected: o/p = i/p
        if(selectedColorCode == -1)
            return inputImage;

        cvtColor(inputImage, outputImage, selectedColorCode);
        /* As Grayscale is single channel
             * Converting to 3 channel matrix is
             * important to display as QPixMap in QLabel
             */

        return outputImage;
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

private slots:
void colorConvRadioButtonClicked(int colorConvCode){
    this->colorConvCode = colorConvCode;
}

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
void initWidget() override
{
    for(int jCount = 0; jCount < colorCodesAll.size(); jCount++)
    {
        QRadioButton *radioButton =
                new QRadioButton(colorCodesAll[jCount].second);
        if(jCount == 0)
            radioButton->setChecked(true);

        vBoxSub->addWidget(radioButton);

        connect(radioButton, &QRadioButton::clicked, this,
                [=]() {
            colorConvRadioButtonClicked(jCount);
        });
    }

    BaseConfigWidget::initWidget();
}
};
