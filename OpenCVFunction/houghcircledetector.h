#ifndef HOUGHCIRCLEDETECTOR_H
#define HOUGHCIRCLEDETECTOR_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QRadioButton>
#include <QCheckBox>

#include "Utils/baseconfigwidget.h"

class HoughCircleDetector: public QWidget, public BaseConfigWidget
{
    Q_OBJECT

public:
    HoughCircleDetector()
    {
        operationName = "Hough Circle Detector";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=houghcircles#houghcircles";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat grayImage;

        cvtColor(inputImage, grayImage, CV_BGR2GRAY);

        if(enableBlurCB->isChecked())
            blur(inputImage, grayImage, cv::Size(3,3));

        std::vector<cv::Vec3f> circles;

        /// Apply the Hough Transform to find the circles
        HoughCircles(grayImage, circles, CV_HOUGH_GRADIENT,
                     1, grayImage.rows/8, 200, 100, 0, 0 );

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

    ~HoughCircleDetector()
    {
        printf("Hough Circle destroyed\n");
    }

private:
    QCheckBox* enableBlurCB = new QCheckBox("Enable Blur");

    void initWidget()
    {
        vBoxSub->addWidget(enableBlurCB);
        BaseConfigWidget::initWidget();
    }

};

#endif // HOUGHCIRCLEDETECTOR_H
