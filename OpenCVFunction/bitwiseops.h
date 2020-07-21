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
#include "Utils/captureinputsource.h"

class BitWise: public BaseConfigWidget
{
    Q_OBJECT
public:
    enum BitWiseLogic{AND, OR, XOR, NOT};
    QMap <BitWiseLogic, QString> logicNameMap = {
        {AND, "AND"},
        {OR, "OR"},
        {XOR, "XOR"},
        {NOT, "NOT"}
    };
    BitWise(BitWiseLogic bitWiseLogic): logic(bitWiseLogic)
    {
        operationName = "Bitwise " + logicNameMap.value(logic, "Unknown");
        moreInfoLink = ""; // TODO
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        // TODO
        cv::Mat outputImage;
        cv::Mat inpputImageChanneled;

        cv::cvtColor(inputImage, inpputImageChanneled, cv::COLOR_GRAY2BGR);

        cv::bitwise_and(inpputImageChanneled, CaptureInputSource::img, outputImage);

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
const BitWiseLogic logic;

void initWidget() override
{
    // TODO
    BaseConfigWidget::initWidget();
}
};
