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

#include "OpenCVFunction/inrange.h"

#include "CustomWidgets/sliderlayout.h"

InRange::InRange()
{
    operationName = "InRange";
    moreInfoLink = "https://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html?highlight=inrange#inrange";
    this->initWidget();
}

cv::Mat InRange::getProcessedImage(cv::Mat inputImage) try
{
    if(channelNos != inputImage.channels())
    {
        channelNos = inputImage.channels();
        emit refreshWidget();
        qDebug() << "Refreshed Parameter Adjustment Widget";
    }

    cv::Mat outputImage = cv::Mat::zeros(inputImage.size(), CV_8U);

    if(static_cast<int>(lLimits->size()) == channelNos
            && static_cast<int>(hLimits->size()) == channelNos)
    {
        cv::inRange(inputImage,
                    *lLimits,
                    *hLimits,
                    outputImage);
    }

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

void InRange::initWidget()
{
    connect(this, SIGNAL(refreshWidget()), this, SLOT(changeSliderNumbers()));

    BaseConfigWidget::initWidget();
}

void InRange::changeSliderNumbers()
{
    lLimits->clear();
    hLimits->clear();

    qDeleteAll(vBoxSub->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));

    // TODO: Add Max Limit according to matrix pixel byte size eg 255 for 8 byte
    for(int i = 0; i < channelNos; i++)
    {
        lLimits->push_back(0);
        hLimits->push_back(100);
        SliderLayout* lSliderLayout = new SliderLayout(
                    QString("Channel ") + QString::number(i) + QString(" Low\n[0-255]"),
                    lLimits->back(), 0, 255, 200);
        connect(lSliderLayout, &SliderLayout::sliderValueChanged,
                this, [=](int value) { lLimits->at(i) = value; });
        vBoxSub->addLayout(lSliderLayout);

        SliderLayout* hSliderLayout = new SliderLayout(
                    QString("Channel ") + QString::number(i) + QString(" High\n[0-255]"),
                    hLimits->back(), 0, 255, 200);
        connect(hSliderLayout, &SliderLayout::sliderValueChanged,
                this, [=](int value) { hLimits->at(i) = value; });
        vBoxSub->addLayout(hSliderLayout);
    }

    BaseConfigWidget::initWidget();
}
