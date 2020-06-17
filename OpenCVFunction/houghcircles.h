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

#ifndef HOUGHCIRCLEDETECTOR_H
#define HOUGHCIRCLEDETECTOR_H

// QT libs
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/sliderlayout.h"
#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/applyresetbuttonlayout.h"
#include "CustomWidgets/dividerline.h"

#include "Utils/constants.h"
#include "Utils/utils.h"

class HoughCircles: public BaseConfigWidget
{
    Q_OBJECT
public:
    HoughCircles()
    {
        operationName = "Hough Circle Detector";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=houghcircles#houghcircles";

        lineEditsWithParams.push_back(std::make_pair(dpLineEditLayout, dp));
        lineEditsWithParams.push_back(std::make_pair(minDistLayout, minDist));
        lineEditsWithParams.push_back(std::make_pair(param1Layout, param1));
        lineEditsWithParams.push_back(std::make_pair(param2Layout, param2));
        lineEditsWithParams.push_back(std::make_pair(minRadiusLayout, minRadius));
        lineEditsWithParams.push_back(std::make_pair(maxRadiusLayout, maxRadius));

        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        cv::Mat grayImage;

        cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

        if(*minDist == -1.0)
        {
            *minDist = grayImage.rows/8;
            minDistLayout->setText(*minDist);
        }

        std::vector<cv::Vec3f> circles;

        /// Apply the Hough Transform to find the circles
        cv::HoughCircles(grayImage, circles, cv::HOUGH_GRADIENT,
                         dp->toInt(), minDist->toDouble(), param1->toDouble(),
                         param2->toDouble(), minRadius->toInt(), maxRadius->toInt());

        /// Draw the circles detected
        for( size_t i = 0; i < circles.size(); i++ )
        {
            cv::Point center(cvRound(circles[i][0]),
                    cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle center
            circle(inputImage, center, 3,
                   cv::Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle(inputImage, center, radius,
                   cv::Scalar(0,0,255), 3, 8, 0 );
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

    ~HoughCircles()
    {
        printf("Hough Circle destroyed\n");
    }

private slots:
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
        *dp = 1;
        *minDist = -1.0;
        *param1 = 100.0;
        *param2 = 100.0;
        *minRadius = 0;
        *maxRadius = 0;

        for(std::pair<LineEditLayout*, QVariant*> lineEditWithParam : lineEditsWithParams)
            lineEditWithParam.first->setText(lineEditWithParam.second->toString());
    }

private:

    QVariant* dp = new QVariant(1);
    QVariant* minDist = new QVariant(-1.0);
    QVariant* param1 = new QVariant(200.0);
    QVariant* param2 = new QVariant(100.0);
    QVariant* minRadius = new QVariant(0);
    QVariant* maxRadius = new QVariant(0);

    QComboBox* selectMethodComboBox = new QComboBox();

    LineEditLayout* dpLineEditLayout = new LineEditLayout("dp", *dp);
    LineEditLayout* minDistLayout = new LineEditLayout("minDist", "NA");
    LineEditLayout* param1Layout = new LineEditLayout("param1", *param1);
    LineEditLayout* param2Layout = new LineEditLayout("param2", *param2);
    LineEditLayout* minRadiusLayout = new LineEditLayout("minRadius", *minRadius);
    LineEditLayout* maxRadiusLayout = new LineEditLayout("maxRadius", *maxRadius);

    QVector<std::pair<LineEditLayout*, QVariant*>> lineEditsWithParams;

    ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

    void initWidget()
    {
        QDoubleValidator* minDistValidator = new QDoubleValidator();

        minDistValidator->setBottom(0);
        minDistValidator->setDecimals(2);

        QIntValidator* dpValidator = new QIntValidator();
        dpValidator->setBottom(0);
        dpLineEditLayout->lineEdit->setValidator(dpValidator);
        minDistLayout->lineEdit->setValidator(minDistValidator);
        // TODO: Add validators to other fields if required

        connect(applyResetBox, SIGNAL(applyClicked()),
                this, SLOT(applyClicked()));
        connect(applyResetBox, SIGNAL(resetClicked()),
                this, SLOT(resetClicked()));

        QLabel* selectMethodLabel = new QLabel("Select Method");
        selectMethodComboBox->addItem("CV_HOUGH_GRADIENT");
        QHBoxLayout* selectMethodHBox = new QHBoxLayout;
        selectMethodHBox->addWidget(selectMethodLabel);
        selectMethodHBox->addWidget(selectMethodComboBox);
        vBoxSub->addLayout(selectMethodHBox);

        for(std::pair<LineEditLayout*, QVariant*> lineEditWithParam : lineEditsWithParams)
            vBoxSub->addLayout(lineEditWithParam.first);

        vBoxSub->addLayout(applyResetBox);

        BaseConfigWidget::initWidget();
    }
};

#endif // HOUGHCIRCLEDETECTOR_H
