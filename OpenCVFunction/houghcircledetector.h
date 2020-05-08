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
        cv::Mat outputImage;

        if(enableBlurCB->isChecked())
            blur( inputImage, outputImage, cv::Size(3,3));

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
