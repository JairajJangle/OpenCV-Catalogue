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

#ifndef HISTOGRAMH
#define HISTOGRAMH

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/baseconfigwidget.h"

class HistogramCalculation : public BaseConfigWidget
{
    Q_OBJECT
public:
    HistogramCalculation()
    {
        operationName = "Histogram Calculation";
        moreInfoLink = "https://docs.opencv.org/3.4/d6/dc7/group__imgproc_Hist.html#ga4b2b5fd75503ff9e6844cc4dcdaed35d";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        std::vector<cv::Mat> bgrPlanes;
        split(inputImage, bgrPlanes);

        const float* histRange = {range};

        cv::Mat bHist, gHist, rHist;

        /**
         * Conditioning on number of channels of @param inputImage is done
         * to prevent Segmentation faults while accessing more number of
         * channels than the size of @param bgrPlanes after above split operation
         */
        if(inputImage.channels() >= 1)
            calcHist(&bgrPlanes[0], 1, 0, cv::Mat(), bHist, 1,
                    &histSize, &histRange, uniform,
                    accumulate);

        if(inputImage.channels() >= 2)
            calcHist(&bgrPlanes[1], 1, 0, cv::Mat(), gHist, 1,
                    &histSize, &histRange, uniform,
                    accumulate);

        if(inputImage.channels() >= 3)
            calcHist(&bgrPlanes[2], 1, 0, cv::Mat(), rHist, 1,
                    &histSize, &histRange, uniform,
                    accumulate);

        int hist_w = 512, histH = 400;
        int bin_w = cvRound((double)hist_w/histSize);

        cv::Mat histImage( histH, hist_w, CV_8UC3, cv::Scalar( 0,0,0));

        normalize(bHist, bHist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
        normalize(gHist, gHist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
        normalize(rHist, rHist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

        for(int i = 1; i < histSize; i++)
        {
            if(inputImage.channels() >= 1)
                line(histImage, cv::Point(bin_w*(i-1), histH - cvRound(bHist.at<float>(i-1))),
                     cv::Point(bin_w*(i), histH - cvRound(bHist.at<float>(i))),
                     cv::Scalar(255, 0, 0), 2, 8, 0);
            if(inputImage.channels() >= 2)
                line(histImage, cv::Point( bin_w*(i-1), histH - cvRound(gHist.at<float>(i-1))),
                     cv::Point(bin_w*(i), histH - cvRound(gHist.at<float>(i))),
                     cv::Scalar(0, 255, 0), 2, 8, 0);
            if(inputImage.channels() >= 3)
                line(histImage, cv::Point( bin_w*(i-1), histH - cvRound(rHist.at<float>(i-1))),
                     cv::Point(bin_w*(i), histH - cvRound(rHist.at<float>(i))),
                     cv::Scalar(0, 0, 255), 2, 8, 0);
        }

        /**
         *  @param histImage is of CV_8UC3 type
         */
        return histImage;
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

~HistogramCalculation()
{
    printf("Histogram Calculation destroyed\n");
}

private:
int histSize = 256;
bool uniform = true, accumulate = false;

float range[2]; //the upper boundary is exclusive

QCheckBox* uniformCB = new QCheckBox("uniform");
QCheckBox* accumulateCB = new QCheckBox("accumulate");

void initWidget()
{
    uniformCB->setChecked(true);
    range[0] = 0; //the upper boundary is exclusive
    range[1] = 256;
    // TODO add parameter control

    // FIXME: Handle uniform false value
    //        vBoxSub->addWidget(uniformCB);
    //        vBoxSub->addWidget(accumulateCB);

    BaseConfigWidget::initWidget();
}
};

#endif // HISTOGRAMH
