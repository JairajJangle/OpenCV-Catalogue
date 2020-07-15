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
#include <QRegExpValidator>

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

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        cv::Mat outputImage;

        switch (selectedTech) {
        case KNN:
            pKNN->apply(inputImage, outputImage, learningRate);
            break;
        case MOG:
            pMOG->apply(inputImage, outputImage, learningRate);
            break;
        case MOG2:
            pMOG2->apply(inputImage, outputImage, learningRate);
            break;
        case GMG:
            pGMG->apply(inputImage, outputImage, learningRate);
            break;
        case GSOC:
            pGSOC->apply(inputImage, outputImage, learningRate);
            break;
        case CNT:
            pCNT->apply(inputImage, outputImage, learningRate);
            break;
        case LSBP:
            pLSBP->apply(inputImage, outputImage, learningRate);
            break;
        }

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

    ~BackgroundSubtraction()
    {
        qDebug() << "Blur destroyed";
    }

private slots:
    void bkgSubTechChanged(int bkgSubTech){
        selectedTech = bkgSubTech;
    }

    void applyChangesClicked(){
        learningRate = learningRateEditLayout->getText().toDouble();
    }

    void resetChangesClicked(){
        learningRate = 0.1;
        learningRateEditLayout->setText(QString::number(learningRate));
    }

    void resetAnchorClicked(){
        begin = cv::Point(-1, -1);
    }

private:
    enum MotionSubtractionTypes{
        KNN, MOG, MOG2, GMG, GSOC, CNT, LSBP
        /* More at: https://docs.opencv.org/3.4/d7/df6/classcv_1_1BackgroundSubtractor.html */
    };

    cv::Ptr< cv::BackgroundSubtractor> pMOG;
    cv::Ptr< cv::BackgroundSubtractor> pMOG2;
    cv::Ptr< cv::BackgroundSubtractor> pGMG;
    cv::Ptr< cv::BackgroundSubtractor> pKNN;
    cv::Ptr< cv::BackgroundSubtractor> pGSOC;
    cv::Ptr< cv::BackgroundSubtractor> pCNT;
    cv::Ptr< cv::BackgroundSubtractor> pLSBP;

    QVector<QString> bkgSubTechs =
    {
        {GET_VARIABLE_NAME(KNN)},
        {GET_VARIABLE_NAME(MOG)},
        {GET_VARIABLE_NAME(MOG2)},
        {GET_VARIABLE_NAME(GMG)},
        {GET_VARIABLE_NAME(GSOC)},
        {GET_VARIABLE_NAME(CNT)},
        {GET_VARIABLE_NAME(LSBP)},
    };

    int selectedTech = KNN;

    double learningRate = 0.1;
    LineEditLayout* learningRateEditLayout  = new LineEditLayout("Learning Rate\n[0-1]",
                                                                 learningRate,
                                                                 150,
                                                                 150);

    ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

    void initWidget()
    {
        connect(applyResetBox, SIGNAL(applyClicked()),
                this, SLOT(applyChangesClicked()));
        connect(applyResetBox, SIGNAL(resetClicked()),
                this, SLOT(resetChangesClicked()));

        learningRateEditLayout->lineEdit->setValidator(
                    new QRegExpValidator(QRegExp(RegExps::decimal0To1)));

        pKNN = cv::createBackgroundSubtractorKNN(1,2000.0,false); //int history=500, double dist2Threshold=400.0, bool detectShadows=true
        pMOG =  cv::bgsegm::createBackgroundSubtractorMOG();
        pMOG2 = cv::createBackgroundSubtractorMOG2();
        pGMG = cv::bgsegm::createBackgroundSubtractorGMG();
        pGSOC = cv::bgsegm::createBackgroundSubtractorGSOC();
        pCNT = cv::bgsegm::createBackgroundSubtractorCNT();
        pLSBP = cv::bgsegm::createBackgroundSubtractorLSBP();

        for(int jCount = 0; jCount < bkgSubTechs.size(); jCount++)
        {
            QRadioButton *radioButton =
                    new QRadioButton(bkgSubTechs[jCount]);
            if(jCount == 0)
                radioButton->setChecked(true);

            vBoxSub->addWidget(radioButton);

            connect(radioButton, &QRadioButton::clicked, this,
                    [=]() {
                bkgSubTechChanged(jCount);
            });
        }
        vBoxSub->addLayout(learningRateEditLayout);
        vBoxSub->addLayout(applyResetBox);

        BaseConfigWidget::initWidget();
    }
};
