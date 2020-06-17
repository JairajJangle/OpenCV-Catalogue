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

#ifndef HARRISCORNERDETECTOR_H
#define HARRISCORNERDETECTOR_H


// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QMetaEnum>

#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/sliderlayout.h"
#include "CustomWidgets/dividerline.h"
#include "CustomWidgets/applyresetbuttonlayout.h"

#include "Utils/utils.h"

class HarrisCornerDetector : public BaseConfigWidget
{
    Q_OBJECT

public:
    HarrisCornerDetector()
    {
        operationName = "Harris Corner Detector";
        moreInfoLink = "https://docs.opencv.org/3.4/dd/d1a/group__imgproc__feature.html#gac1fc3598018010880e370e2f709b4345";

        lineEditsWithParams.push_back(std::make_pair(blockSizeLayout, blockSize));
        lineEditsWithParams.push_back(std::make_pair(apertureSizeLayout, apertureSize));
        lineEditsWithParams.push_back(std::make_pair(kLayout, k));

        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        blockSizeLayout->setText(borderTypeComboBox->currentData());

        cv::Mat inputImageGray, outputImage,
                inputNorm, inputNormScaled;

        inputImage.copyTo(outputImage);

        cvtColor(inputImage, inputImageGray, cv::COLOR_BGR2GRAY);

        cv::Mat dst = cv::Mat::zeros(inputImage.size(), CV_32FC1);

        cornerHarris(inputImageGray, dst,
                     blockSize->toInt(), apertureSize->toInt(), k->toDouble(),
                     borderType->toInt());
        normalize(dst, inputNorm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
        convertScaleAbs(inputNorm, inputNormScaled);

        for(int i = 0; i < inputNorm.rows ; i++)
        {
            for(int j = 0; j < inputNorm.cols; j++)
            {
                if(static_cast<int>(inputNorm.at<float>(i,j)) > threshold)
                {
                    circle(outputImage, cv::Point(j,i), 5,
                           cv::Scalar(0, 0, 255), 2, 8, 0);
                }
            }
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

    ~HarrisCornerDetector()
    {
        printf("Harris Corner Detector destroyed\n");
    }

private slots:
    void threshChanged(int value)
    {
        threshold = value;
    }

    void applyClicked()
    {
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

    void resetClicked()
    {
        *blockSize = 2;
        *apertureSize = 3;
        *k = 0.04;

        for(std::pair<LineEditLayout*, QVariant*> lineEditWithParam : lineEditsWithParams)
            lineEditWithParam.first->setText(lineEditWithParam.second->toString());

        borderTypeComboBox->setCurrentText("BORDER_DEFAULT");
    }

    void borderTypeChanged(int index)
    {
        *borderType = borderTypeComboBox->itemData(index);
    }

private:
    int threshold = 200;

    // TODO: Add ToolTip for Theshold
    SliderLayout* threshSliderLayout = new SliderLayout("Threshold\n[0-255]",
                                                        threshold, 0, 255, 190);

    QVariant* blockSize = new QVariant(2);
    // FIXME: Kernel size should be odd and less than 31
    QVariant* apertureSize = new QVariant(3);
    QVariant* k = new QVariant(0.04);
    QVariant* borderType = new QVariant(cv::BORDER_DEFAULT);

    LineEditLayout* blockSizeLayout = new LineEditLayout("blockSize", *blockSize);
    LineEditLayout* apertureSizeLayout = new LineEditLayout("ksize", *apertureSize);
    LineEditLayout* kLayout = new LineEditLayout("k", *k);
    QComboBox* borderTypeComboBox = new QComboBox();

    QVector<std::pair<LineEditLayout*, QVariant*>> lineEditsWithParams;

    ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

    void initWidget()
    {
        borderTypeComboBox->addItem("BORDER_CONSTANT", cv::BORDER_CONSTANT);
        borderTypeComboBox->addItem("BORDER_REPLICATE", cv::BORDER_REPLICATE);
        borderTypeComboBox->addItem("BORDER_REFLECT", cv::BORDER_REFLECT);
        /*!
         * borderTypeComboBox->addItem( "BORDER_WRAP", 3);
         * BORDER_WRAP is not supported, see @var moreInfoLink page
         */
        borderTypeComboBox->addItem("BORDER_DEFAULT", cv::BORDER_DEFAULT);
        borderTypeComboBox->addItem("BORDER_REFLECT_101", cv::BORDER_REFLECT_101);
        /*!
         * FIXME:
         * borderTypeComboBox->addItem("BORDER_TRANSPARENT", cv::BORDER_TRANSPARENT);
         * BORDER_TRANSPARENT is causing crash
         */
        borderTypeComboBox->addItem("BORDER_REFLECT101", cv::BORDER_REFLECT101);
        borderTypeComboBox->addItem("BORDER_ISOLATED", cv::BORDER_ISOLATED);
        borderTypeComboBox->setCurrentText("BORDER_DEFAULT");

        for(std::pair<LineEditLayout*, QVariant*> lineEditWithParam : lineEditsWithParams)
            vBoxSub->addLayout(lineEditWithParam.first);

        connect(applyResetBox, SIGNAL(applyClicked()),
                this, SLOT(applyClicked()));
        connect(applyResetBox, SIGNAL(resetClicked()),
                this, SLOT(resetClicked()));

        vBoxSub->addLayout(applyResetBox);

        QHBoxLayout* borderTypeHBox = new QHBoxLayout;
        borderTypeHBox->addWidget(new QLabel("borderType"));
        borderTypeHBox->setSpacing(30);

        connect(borderTypeComboBox, SIGNAL(activated(int)),
                this, SLOT(borderTypeChanged(int)));

        borderTypeHBox->addWidget(borderTypeComboBox);
        borderTypeHBox->insertStretch( -1, 1 );
        vBoxSub->addLayout(borderTypeHBox);

        vBoxSub->addWidget(new DividerLine(this));

        vBoxSub->addLayout(threshSliderLayout);
        connect(threshSliderLayout, SIGNAL(sliderValueChanged(int)),
                this, SLOT(threshChanged(int)));

        BaseConfigWidget::initWidget();
    }
};

#endif // HARRISCORNERDETECTOR_H
