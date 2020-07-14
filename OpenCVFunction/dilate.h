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
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/duallineeditlayout.h"

class Dilate : public BaseConfigWidget
{
    Q_OBJECT
public:
    Dilate()
    {
        operationName = "Dilate";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#dilate";
        initWidget();
    }

    ~Dilate()
    {
        qDebug() << "Dilate Destroyed";
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        cv::Mat outputImage;

        cv::Mat element = cv::getStructuringElement(kernelMorphShape, kSize, kernelAnchor);

        cv::dilate(inputImage, outputImage, element);

        // dilate(inputImage, outputImage, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

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

protected:
int dilationSize = 6;
int kernelMorphShape = cv::MORPH_CROSS; // cv::MorphShapes
cv::Size kSize = cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1);
cv::Point kernelAnchor = cv::Point(dilationSize, dilationSize);

const int lineEditW = 70;

DualLineEditLayout *kSizeDLEL = new DualLineEditLayout("Kernel Size",
                                                       qMakePair(kSize.width,kSize.height),
                                                       70);
void initWidget()
{
    vBoxSub->setSpacing(15);

    QIntValidator* kSizeValidator = new QIntValidator();
    kSizeValidator->setBottom(1);

    kSizeDLEL->setValidator(kSizeValidator);

    vBoxSub->addLayout(kSizeDLEL);

    // TODO: Add Config widgets
    BaseConfigWidget::initWidget();
}
};
