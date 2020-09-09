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
#include "CustomWidgets/duallineeditlayout.h"
#include "CustomWidgets/applyresetbuttonlayout.h"
#include "Utils/captureinputsource.h"

class Resize : public BaseConfigWidget
{
    Q_OBJECT
public:
    Resize()
    {
        operationName = "Resize";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html?highlight=resize#resize";
        this->initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        cv::Mat outputImage;

        cv::resize(inputImage, outputImage, resolution);
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

private:
cv::Size resolution = cv::Size(640, 480);
DualLineEditLayout* resDLEL = new DualLineEditLayout("Size",
                                                     qMakePair(resolution.width,
                                                               resolution.height),
                                                     80);
ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

void initWidget() override
{
    resolution = cv::Size(CaptureInputSource::img.cols,
                          CaptureInputSource::img.rows);

    connect(applyResetBox, &ApplyResetButtonLayout::applyClicked,
            this, [=](){
        resolution = cv::Size(resDLEL->getTexts().first.toInt(),
                              resDLEL->getTexts().second.toInt());
    });
    connect(applyResetBox, &ApplyResetButtonLayout::resetClicked,
            this, [=](){
        resolution = cv::Size(CaptureInputSource::img.cols,
                              CaptureInputSource::img.rows);

        resDLEL->setText(qMakePair(resolution.width,
                                   resolution.height));
    });

    QIntValidator* resValidator = new QIntValidator();
    resValidator->setBottom(1);

    resDLEL->setValidator(resValidator);

    vBoxSub->addLayout(resDLEL);
    vBoxSub->addSpacing(10);
    vBoxSub->addLayout(applyResetBox);

    BaseConfigWidget::initWidget();
}
};
