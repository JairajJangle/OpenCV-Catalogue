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
#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/dividerline.h"

class SubImage : public BaseConfigWidget
{
    Q_OBJECT
public:
    SubImage()
    {
        operationName = "SubImage";
        // FIXME: Add Doc URL
        moreInfoLink = "";
        this->initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        cv::Mat outputImage;

        if(startPoint.x == endPoint.x
                || startPoint.y == endPoint.y)
            return inputImage;

        cv::Mat ROI(inputImage, cv::Rect(startPoint, endPoint));

        // Copy the data into new matrix
        ROI.copyTo(outputImage);

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
cv::Point startPoint = cv::Point(0, 0);
cv::Point endPoint = cv::Point(0, 0);

QLabel* factorNote  = new QLabel("Drag and drop mouse to extract that sub-image");

ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout(true, false);

private slots:
void mouseLBClicked(QPoint point) override
{
    startPoint = cv::Point(point.x(), point.y());
    endPoint = cv::Point(point.x(), point.y());
}
void mouseLBReleased(QPoint point) override
{
    endPoint = cv::Point(point.x(), point.y());
}

void initWidget() override
{
    QFont font = factorNote->font();
    font.setPointSize(8);
    factorNote->setFont(font);
    factorNote->setAlignment(Qt::AlignCenter);

    vBoxSub->addWidget(new DividerLine(1));
    vBoxSub->addWidget(factorNote);
    vBoxSub->addWidget(new DividerLine(1));
    vBoxSub->addLayout(applyResetBox);

    connect(applyResetBox, &ApplyResetButtonLayout::resetClicked,
            this, [=](){
        startPoint = cv::Point(0, 0);
        endPoint = cv::Point(0, 0);
    });

    BaseConfigWidget::initWidget();
}
};
