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

#ifndef HOUGHLINES_H
#define HOUGHLINES_H

// QT libs
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/sliderlayout.h"
#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/applyresetbuttonlayout.h"

#include "Utils/constants.h"
#include "Utils/utils.h"

#include <iostream>

class HoughLines: public BaseConfigWidget
{
    Q_OBJECT
public:
    HoughLines()
    {
        operationName = "Hough Lines Detector";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=HoughLines#houghlines";

        lineEditsWithParams.push_back(std::make_pair(rhoLineEditLayout, rho));
        lineEditsWithParams.push_back(std::make_pair(thetaLayout, theta));
        lineEditsWithParams.push_back(std::make_pair(thresholdLayout, threshold));
        lineEditsWithParams.push_back(std::make_pair(srnLayout, srn));
        lineEditsWithParams.push_back(std::make_pair(stnLayout, stn));

        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        m.lock();

        cv::Mat dst, cdst; // CDST contains canny + lines
        // TODO make Canny params customizable
        Canny(inputImage, dst, 50, 200, 3);
        cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);

        std::vector<cv::Vec4i> lines;
        HoughLinesP(dst, lines, rho->toDouble(), theta->toDouble(), threshold->toInt(), srn->toDouble(), stn->toDouble());
        for(size_t i = 0; i < lines.size(); i++)
        {
            cv::Vec4i l = lines[i];
            line(cdst, cv::Point(l[0], l[1]),
                    cv::Point(l[2], l[3]), cv::Scalar(0,0,255),
                    3, cv::LINE_AA);
        }

        for (size_t i=0; i<lines.size(); i++) {
            cv::Vec4i l = lines[i];
            cv::line(inputImage, cv::Point(l[0], l[1]),
                    cv::Point(l[2], l[3]),
                    cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
        }

        m.unlock();
        return inputImage;
    }

    ~HoughLines()
    {
        printf("Hough Lines destroyed\n");
    }

private slots:
    void blurKernelChanged(int value){
        blurKernelSize = value;
    }

    void blurCBClicked(bool isChecked){
        isBlurEnabled = isChecked;

        blurKernelSliderLayout->setVisible(isChecked);
    }

    void applyClicked(){
        bool paramsApplied = true;
        for(std::pair<LineEditLayout*, QVariant*> lineEditWithParam : lineEditsWithParams)
        {
            if(!lineEditWithParam.first->getText().isEmpty())
                lineEditWithParam.second->setValue(QVariant(lineEditWithParam.first->getText()));
            else
            {
                paramsApplied = false;
                break;
            }
        }

        if(!paramsApplied)
        {
            // TODO: Update error label message
        }
    }

    void resetClicked(){
        *rho = 1.0;
        *theta = CV_PI/180;
        *threshold = 50;
        *srn = 50.0;
        *stn = 10.0;

        for(std::pair<LineEditLayout*, QVariant*> lineEditWithParam : lineEditsWithParams)
            lineEditWithParam.first->setText(lineEditWithParam.second->toString());

        // Special case:
        thetaLayout->setText(Numeric::setPrecision(theta->toDouble(), 6));
    }

private:
    int blurKernelSize = 3;
    bool isBlurEnabled = true;
    QCheckBox* enableBlurCB = new QCheckBox("Enable Blur");
    SliderLayout* blurKernelSliderLayout = new SliderLayout("Blur kernel\nsize", blurKernelSize);

    QVariant* rho = new QVariant(1); // double
    QVariant* theta = new QVariant(CV_PI/180); // double
    QVariant* threshold = new QVariant(50); // int
    QVariant* srn = new QVariant(50.0); // double
    QVariant* stn = new QVariant(10.0); // double

    LineEditLayout* rhoLineEditLayout = new LineEditLayout("rho", *rho);
    LineEditLayout* thetaLayout = new LineEditLayout("theta", *theta, 150);
    LineEditLayout* thresholdLayout = new LineEditLayout("threshold", *threshold);
    LineEditLayout* srnLayout = new LineEditLayout("srn", *srn);
    LineEditLayout* stnLayout = new LineEditLayout("stn", *stn);

    QVector<std::pair<LineEditLayout*, QVariant*>> lineEditsWithParams;

    ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

    void initWidget()
    {
        thetaLayout->setText(Numeric::setPrecision(theta->toDouble(), 6));

        QDoubleValidator* rhoValidator = new QDoubleValidator();
        QDoubleValidator* thetaValidator = new QDoubleValidator();
        QIntValidator* thresholdValidator = new QIntValidator();
        QDoubleValidator* srnValidator = new QDoubleValidator();
        QDoubleValidator* stnValidator = new QDoubleValidator();

        thetaValidator->setBottom(0);
        thetaValidator->setDecimals(6);
        thetaLayout->lineEdit->setValidator(thetaValidator);

        rhoValidator->setBottom(0);
        rhoValidator->setDecimals(4);
        rhoLineEditLayout->lineEdit->setValidator(rhoValidator);

        thresholdValidator->setBottom(0);
        thresholdLayout->lineEdit->setValidator(thresholdValidator);

        srnValidator->setBottom(0);
        srnValidator->setDecimals(4);
        srnLayout->lineEdit->setValidator(srnValidator);

        stnValidator->setBottom(0);
        stnValidator->setDecimals(4);
        stnLayout->lineEdit->setValidator(stnValidator);

        // TODO: Add validators to other fields if required

        enableBlurCB->setChecked(true);
        connect(enableBlurCB, SIGNAL(clicked(bool)),
                this, SLOT(blurCBClicked(bool)));
        connect(blurKernelSliderLayout, SIGNAL(sliderValueChanged(int)),
                this, SLOT(blurKernelChanged(int)));

        connect(applyResetBox, SIGNAL(applyClicked()),
                this, SLOT(applyClicked()));
        connect(applyResetBox, SIGNAL(resetClicked()),
                this, SLOT(resetClicked()));

        for(std::pair<LineEditLayout*, QVariant*> lineEditWithParam : lineEditsWithParams)
            vBoxSub->addLayout(lineEditWithParam.first);

        vBoxSub->addLayout(applyResetBox);

        QFrame* separatorLine = new QFrame(this);
        separatorLine->setObjectName(QString::fromUtf8("line"));
        separatorLine->setGeometry(QRect(320, 150, 118, 3));
        separatorLine->setFrameShape(QFrame::HLine);
        separatorLine->setFrameShadow(QFrame::Sunken);
        separatorLine->setFixedHeight(20);
        vBoxSub->addWidget(separatorLine);

        // TODO: Add Hough Lines function control trackbars
        vBoxSub->addWidget(enableBlurCB);
        vBoxSub->addLayout(blurKernelSliderLayout);

        BaseConfigWidget::initWidget();
    }
};


#endif // HOUGHLINES_H
