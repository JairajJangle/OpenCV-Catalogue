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

#ifndef INRANGE_H
#define INRANGE_H

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/sliderlayout.h"

class InRange : public BaseConfigWidget
{
    Q_OBJECT
public:
    InRange()
    {
        operationName = "InRange";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html?highlight=inrange#inrange";
        this->initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        m.lock();

        if(channelNos != inputImage.channels())
        {
            channelNos = inputImage.channels();
            changeSliderNumbers();
        }

        cv::Mat outputImage;

        if(inputImage.channels() == 1)
            cv::inRange(inputImage,
                        cv::Scalar(c1Low),
                        cv::Scalar(c1High),
                        outputImage);

        else if(inputImage.channels() == 3)
            cv::inRange(inputImage,
                        cv::Scalar(c1Low, c2Low, c3Low),
                        cv::Scalar(c1High, c2High, c3High),
                        outputImage);

        m.unlock();
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

~InRange()
{
    printf("InRange destroyed\n");
}

private:
int c1Low = 0;
int c2Low = 0;
int c3Low = 0;

int c1High = 0;
int c2High = 0;
int c3High = 0;

bool isWidgetInitialized;
int channelNos = -1;

SliderLayout* c1LSliderLayout = new SliderLayout("Channel 1 Low\n[0-255]", c1Low, 0, 255, 200);
SliderLayout* c2LSliderLayout = new SliderLayout("Channel 2 Low\n[0-255]", c2Low, 0, 255, 200);
SliderLayout* c3LSliderLayout = new SliderLayout("Channel 3 Low\n[0-255]", c3Low, 0, 255, 200);

SliderLayout* c1HSliderLayout = new SliderLayout("Channel 1 High\n[0-255]", c1High, 0, 255, 200);
SliderLayout* c2HSliderLayout = new SliderLayout("Channel 2 High\n[0-255]", c2High, 0, 255, 200);
SliderLayout* c3HSliderLayout = new SliderLayout("Channel 3 High\n[0-255]", c3High, 0, 255, 200);

void initWidget()
{
    qDeleteAll(vBoxSub->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));

    vBoxSub->addLayout(c1LSliderLayout);
    vBoxSub->addLayout(c2LSliderLayout);
    vBoxSub->addLayout(c3LSliderLayout);

    vBoxSub->addLayout(c1HSliderLayout);
    vBoxSub->addLayout(c2HSliderLayout);
    vBoxSub->addLayout(c3HSliderLayout);

    BaseConfigWidget::initWidget();
    isWidgetInitialized = true;
}

void changeSliderNumbers()
{
    qDeleteAll(vBoxSub->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    // TODO: Add layouts dynamically according to matrix type
}
};

#endif // INRANGE_H
