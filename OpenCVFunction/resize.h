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
#include "CustomWidgets/labelledcombobox.h"
#include "Utils/captureinputsource.h"

class Resize : public BaseConfigWidget
{
    Q_OBJECT
public:
    Resize()
    {
        operationName = "Resize";
        moreInfoLink = "https://docs.opencv.org/4.5.2/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d";
        this->initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        cv::Mat outputImage;

        cv::resize(inputImage, outputImage, resolution,
                   fx.toDouble(), fy.toDouble(),
                   interpolation);
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
DualLineEditLayout* resDLEL = new DualLineEditLayout("dsize",
                                                     qMakePair(resolution.width,
                                                               resolution.height),
                                                     80);

QVariant fx = 0.0;
QVariant fy = 0.0;

QLabel* factorNote  = new QLabel("Either dsize or both fx and fy must be non-zero.");

LineEditLayout* fxLEL = new LineEditLayout("fx", fx);
LineEditLayout* fyLEL = new LineEditLayout("fy", fy);

int interpolation = cv::INTER_LINEAR;
QMap<QString, QVariant> interpolationMethodList = {
    {"INTER_NEAREST", cv::INTER_NEAREST},
    {"INTER_LINEAR", cv::INTER_LINEAR},
    {"INTER_CUBIC", cv::INTER_CUBIC},
    {"INTER_AREA", cv::INTER_AREA},
    {"INTER_LANCZOS4", cv::INTER_LANCZOS4}
};
LabelledComboBox* interpolationLCB =
        new LabelledComboBox("interpolation", interpolationMethodList);

ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

void initWidget() override
{
    QFont font = factorNote->font();
    font.setPointSize(8);
    factorNote->setFont(font);
    factorNote->setAlignment(Qt::AlignCenter);

    QIntValidator* resValidator = new QIntValidator();
    resValidator->setBottom(1);

    resDLEL->setValidator(resValidator);

    vBoxSub->addLayout(resDLEL);
    vBoxSub->addSpacing(10);

    vBoxSub->addWidget(new DividerLine(1));
    vBoxSub->addWidget(factorNote);
    vBoxSub->addWidget(new DividerLine(1));

    QDoubleValidator* fxyValidator = new QDoubleValidator();
    fxyValidator->setBottom(0.0);
    fxLEL->lineEdit->setValidator(new QDoubleValidator);
    fyLEL->lineEdit->setValidator(new QDoubleValidator);

    vBoxSub->addLayout(fxLEL);
    vBoxSub->addLayout(fyLEL);
    vBoxSub->addSpacing(10);

    connect(interpolationLCB, &LabelledComboBox::currentIndexChanged,
            this, [=](int index){
        interpolation = index;
        interpolationLCB->comboBox->setCurrentIndex(index);
    });
    interpolationLCB->comboBox->setCurrentText(
                interpolationMethodList.key(interpolation));
    vBoxSub->addLayout(interpolationLCB);

    vBoxSub->addSpacing(10);
    vBoxSub->addLayout(applyResetBox);

    connect(applyResetBox, &ApplyResetButtonLayout::applyClicked,
            this, [=](){
        resolution = cv::Size(resDLEL->getTexts().first.toInt(),
                              resDLEL->getTexts().second.toInt());

        fx = fxLEL->getText().toDouble();
        fy = fyLEL->getText().toDouble();
    });
    connect(applyResetBox, &ApplyResetButtonLayout::resetClicked,
            this, [=](){
        resolution = cv::Size(CaptureInputSource::img.cols,
                              CaptureInputSource::img.rows);

        resDLEL->setText(qMakePair(resolution.width,
                                   resolution.height));

        fx = 0.0; fxLEL->setText(fx);
        fy = 0.0; fyLEL->setText(fy);
    });

    BaseConfigWidget::initWidget();
}
};
