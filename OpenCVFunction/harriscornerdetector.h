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

#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/sliderlayout.h"

class HarrisCornerDetector : public BaseConfigWidget
{
    Q_OBJECT
public:
    HarrisCornerDetector()
    {
        operationName = "Harris Corner Detector";
        moreInfoLink = "https://docs.opencv.org/3.4/dd/d1a/group__imgproc__feature.html#gac1fc3598018010880e370e2f709b4345";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        m.lock();

        cv::Mat inputImageGray, outputImage,
                inputNorm, inputNormScaled;

        inputImage.copyTo(outputImage);

        cvtColor(inputImage, inputImageGray, cv::COLOR_BGR2GRAY);

        cv::Mat dst = cv::Mat::zeros(inputImage.size(), CV_32FC1);

        cornerHarris(inputImageGray, dst, blockSize, apertureSize, k);
        normalize(dst, inputNorm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
        convertScaleAbs(inputNorm, inputNormScaled);

        for(int i = 0; i < inputNorm.rows ; i++)
        {
            for(int j = 0; j < inputNorm.cols; j++)
            {
                if(static_cast<int>(inputNorm.at<float>(i,j)) > threshold)
                {
                    circle(outputImage, cv::Point(j,i), 5,
                           cv::Scalar(0, 0, 255), 2, 8, 0 );
                }
            }
        }

        m.unlock();
        return outputImage;
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

private:
    int threshold = 200;
    SliderLayout* threshSliderLayout = new SliderLayout("Threshold\n[0-255]", threshold, 0, 255);

    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    void initWidget()
    {
        // TODO add parameter control

        connect(threshSliderLayout, SIGNAL(sliderValueChanged(int)),
                this, SLOT(threshChanged(int)));

        vBoxSub->addLayout(threshSliderLayout);

        BaseConfigWidget::initWidget();
    }
};

#endif // HARRISCORNERDETECTOR_H
