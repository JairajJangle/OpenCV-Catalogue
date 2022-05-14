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

#include "Utils/utils.h"
#include "Utils/constants.h"

#include <opencv2/bgsegm.hpp>

#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/errorlabel.h"
#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/applyresetbuttonlayout.h"

class BackgroundSubtraction : public BaseConfigWidget
{
    Q_OBJECT
public:
    BackgroundSubtraction()
    {
        operationName = "Background Subtraction";
        moreInfoLink = "https://docs.opencv.org/3.4/d7/df6/classcv_1_1BackgroundSubtractor.html";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        cv::Mat outputImage;

        bkgSubTechList.at(selectedTech)->apply(inputImage, outputImage, learningRate);

        cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
        morphologyEx(outputImage, outputImage, cv::MORPH_OPEN, element);

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
void bkgSubTechChanged(int bkgSubTech){
    selectedTech = bkgSubTech;
}

void resetAnchorClicked(){
    begin = cv::Point(-1, -1);
}

private:
QList<cv::Ptr<cv::BackgroundSubtractor>> bkgSubTechList;

// More at: https://docs.opencv.org/3.4/d7/df6/classcv_1_1BackgroundSubtractor.html
QList<QString> bkgSubTechs = { "KNN", "MOG", "MOG2", "GMG", "GSOC", "CNT", "LSBP" };

int selectedTech = 0; // KNN
double learningRate = 0.1;
LineEditLayout* learningRateEditLayout  = new LineEditLayout("Learning Rate\n[0-1]",
                                                             learningRate,
                                                             150,
                                                             150);
ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

void initWidget() override
{
    connect(applyResetBox, &ApplyResetButtonLayout::applyClicked,
            this, [=](){ learningRate = learningRateEditLayout->getText().toDouble(); });
    connect(applyResetBox, &ApplyResetButtonLayout::resetClicked,
            this, [=](){
        learningRate = 0.1;
        learningRateEditLayout->setText(QString::number(learningRate));
    });

    learningRateEditLayout->lineEdit->setValidator(new QDoubleValidator(0, 1, 4));

    bkgSubTechList.append(cv::createBackgroundSubtractorKNN(1,2000.0,false)); // KNN
    bkgSubTechList.append(cv::bgsegm::createBackgroundSubtractorMOG()); // MOG
    bkgSubTechList.append(cv::createBackgroundSubtractorMOG2()); // MOG2
    bkgSubTechList.append(cv::bgsegm::createBackgroundSubtractorGMG()); // GMG
    bkgSubTechList.append(cv::bgsegm::createBackgroundSubtractorGSOC()); // GSOC
    bkgSubTechList.append(cv::bgsegm::createBackgroundSubtractorCNT()); // CNT
    bkgSubTechList.append(cv::bgsegm::createBackgroundSubtractorLSBP()); // LSBP

    for(int ibkgSubTech = 0; ibkgSubTech < bkgSubTechs.size(); ibkgSubTech++)
    {
        QRadioButton *radioButton =
                new QRadioButton(bkgSubTechs[ibkgSubTech]);
        if(ibkgSubTech == 0)
            radioButton->setChecked(true);

        vBoxSub->addWidget(radioButton);

        connect(radioButton, &QRadioButton::clicked, this,
                [=]() {
            selectedTech = ibkgSubTech;
        });
    }
    vBoxSub->addLayout(learningRateEditLayout);
    vBoxSub->addLayout(applyResetBox);

    BaseConfigWidget::initWidget();
}
};
