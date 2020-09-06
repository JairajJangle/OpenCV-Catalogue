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

#include "OpenCVFunction/bitwiseops.h"

BitWise::BitWise()
{
    operationName = "Bitwise Operation";
    moreInfoLink = "";
    initWidget();
}

cv::Mat BitWise::getProcessedImage(cv::Mat inputImage) try
{
    cv::Mat outputImage;
    cv::Mat inputImageChanneled;

    if(inputImage.channels() == 1)
        cv::cvtColor(inputImage, inputImageChanneled, cv::COLOR_GRAY2BGR);
    else if(inputImage.channels() == 3)
        inputImage.copyTo(inputImageChanneled);

    // TODO: Check need to optional parameter: mas in bitwise operations
    switch (selectedLogic) {
    case AND:
        cv::bitwise_and(inputImageChanneled, CaptureInputSource::img, outputImage);
        break;
    case OR:
        cv::bitwise_or(inputImageChanneled, CaptureInputSource::img, outputImage);
        break;
    case XOR:
        cv::bitwise_xor(inputImageChanneled, CaptureInputSource::img, outputImage);
        break;
    case NOT:
        cv::bitwise_not(inputImageChanneled, outputImage);
        break;
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

void BitWise::logicTypeChanged(QVariant value){
    selectedLogic = static_cast<BitWiseLogic>(value.toInt());
    moreInfoLink = baseInfoLink + logicNameMap.value(value).toLower();
    qDebug() << "Selected Bitwise operator: " << selectedLogic;
}

void BitWise::initWidget()
{
    LabelledComboBox* logicTypeLCB = new LabelledComboBox("Bitwise Logic Type", logicNameMap);

    vBoxSub->addLayout(logicTypeLCB);

    connect(logicTypeLCB,SIGNAL(currentDataChanged(QVariant)),
            this,SLOT(logicTypeChanged(QVariant)));

    logicTypeChanged(AND);

    BaseConfigWidget::initWidget();
}
