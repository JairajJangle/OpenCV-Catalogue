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

#include "OpenCVFunction/imageflip.h"

// QT libs
#include <QRadioButton>

ImageFlip::ImageFlip()
{
    operationName = "Image Flip";
    moreInfoLink = "https://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#flip";
    initWidget();
}

cv::Mat ImageFlip::getProcessedImage(cv::Mat inputImage) try
{
    cv::Mat outputImage;
    int selectedFlipFlag = flipFlagsAll.at(flipFlagCode).first;

    // If "No Image Flip" is selected: o/p = i/p
    if(selectedFlipFlag == -99)
        return inputImage;

    flip(inputImage, outputImage, selectedFlipFlag);
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

void ImageFlip::imgFlipRadioButtonClicked(int flipFlagCode){
    this->flipFlagCode = flipFlagCode;
}

void ImageFlip::initWidget()
{
    for(int jCount = 0; jCount < flipFlagsAll.size(); jCount++)
    {
        QRadioButton *radioButton =
                new QRadioButton(flipFlagsAll.at(jCount).second);
        if(jCount == 0)
            radioButton->setChecked(true);

        vBoxSub->addWidget(radioButton);

        connect(radioButton, &QRadioButton::clicked,
                this, [=]() { imgFlipRadioButtonClicked(jCount); });
    }

    BaseConfigWidget::initWidget();
}
