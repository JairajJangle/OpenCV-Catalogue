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
#include "CustomWidgets/sliderlayout.h"
#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/applyresetbuttonlayout.h"
#include "CustomWidgets/dividerline.h"

#include "Utils/constants.h"
#include "Utils/utils.h"

class HoughLines: public BaseConfigWidget
{
    Q_OBJECT
public:
    HoughLines()
    {
        operationName = "Hough Lines Detector";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=HoughLines#houghlines";

        lineEditsWithParams.push_back(qMakePair(rhoLineEditLayout, rho));
        lineEditsWithParams.push_back(qMakePair(thetaLayout, theta));
        lineEditsWithParams.push_back(qMakePair(thresholdLayout, threshold));
        lineEditsWithParams.push_back(qMakePair(srnLayout, srn));
        lineEditsWithParams.push_back(qMakePair(stnLayout, stn));

        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        cv::Mat dst, cdst; // CDST contains canny + lines
        // TODO make Canny params customizable
        Canny(inputImage, dst, 50, 200, 3);
        cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
        explodedView.insert("Grayscale", cdst.clone());

        std::vector<cv::Vec4i> lines;
        HoughLinesP(dst, lines, rho->toDouble(), theta->toDouble(), threshold->toInt(), srn->toDouble(), stn->toDouble());
        for(size_t i = 0; i < lines.size(); i++)
        {
            cv::Vec4i l = lines[i];
            line(cdst, cv::Point(l[0], l[1]),
                    cv::Point(l[2], l[3]), cv::Scalar(0,0,255),
                    3, cv::LINE_AA);
        }

        for (size_t i = 0; i < lines.size(); i++) {
            cv::Vec4i l = lines[i];
            cv::line(inputImage, cv::Point(l[0], l[1]),
                    cv::Point(l[2], l[3]),
                    cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
        }

        return inputImage;
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
void applyClicked(){
    bool paramsApplied = true;
    for(auto& lineEditWithParam : lineEditsWithParams)
    {
        if(!lineEditWithParam.first->getText().isEmpty())
            return lineEditWithParam.second->setValue(QVariant(lineEditWithParam.first->getText()));

        paramsApplied = false;
        break;

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

    for(auto& lineEditWithParam : lineEditsWithParams)
        lineEditWithParam.first->setText(lineEditWithParam.second->toString());

    // Special case:
    thetaLayout->setText(Numeric::setPrecision(theta->toDouble(), 6));
}

private:
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

QVector<QPair<LineEditLayout*, QVariant*>> lineEditsWithParams;

ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

void initWidget() override
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

    connect(applyResetBox, SIGNAL(applyClicked()),
            this, SLOT(applyClicked()));
    connect(applyResetBox, SIGNAL(resetClicked()),
            this, SLOT(resetClicked()));

    for(auto& lineEditWithParam : lineEditsWithParams)
        vBoxSub->addLayout(lineEditWithParam.first);

    vBoxSub->addLayout(applyResetBox);

    BaseConfigWidget::initWidget();
}
};
