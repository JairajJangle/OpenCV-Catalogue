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

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

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
        moreInfoLink = "https://docs.opencv.org/3.4/d6/dc7/group__imgproc__hist.html#ga4b2b5fd75503ff9e6844cc4dcdaed35d";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        m.lock();

        std::vector<cv::Mat> bgr_planes;
        split(inputImage, bgr_planes);

        const float* histRange = {range};

        cv::Mat b_hist, g_hist, r_hist;

        calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1,
                &histSize, &histRange, uniformCB->isChecked(),
                accumulateCB->isChecked());
        calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1,
                &histSize, &histRange, uniformCB->isChecked(),
                accumulateCB->isChecked());
        calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1,
                &histSize, &histRange, uniformCB->isChecked(),
                accumulateCB->isChecked());

        int hist_w = 512, hist_h = 400;
        int bin_w = cvRound((double)hist_w/histSize);

        cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0));
        normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
        normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
        normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

        for(int i = 1; i < histSize; i++)
        {
            line(histImage, cv::Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))),
                 cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
                 cv::Scalar(255, 0, 0), 2, 8, 0);
            line(histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))),
                 cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
                 cv::Scalar(0, 255, 0), 2, 8, 0);
            line(histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))),
                 cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
                 cv::Scalar(0, 0, 255), 2, 8, 0);
        }

        m.unlock();
        return histImage;
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

#endif // HISTOGRAM_H
