// OpenCV Image Flip class
#ifndef IMAGEFLIP_H
#define IMAGEFLIP_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// OpenCV libs
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/core/core.hpp>
#include <Utils/baseconfigwidget.h>

// QT libs
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QLabel>
#include <QSizePolicy>
#include <QSpacerItem>

#include <iostream>

using namespace cv;
using namespace std;

class ImageFlip : public QWidget, public BaseConfigWidget
{
    Q_OBJECT
public:
    ImageFlip()
    {
        operationName = "Image Flip";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#flip";
        initWidget();
    }

    Mat getProcessedImage(Mat inputImage)
    {
        Mat outputImage;
        int selectedFlipFlag = flipFlagsAll.at(flipFlagCode).first;

        // If "No Image Flip" is selected: o/p = i/p
        if(selectedFlipFlag == -99)
            return inputImage;
        else
            flip(inputImage, outputImage, selectedFlipFlag);

        return outputImage;
    }

    ~ImageFlip()
    {
        printf("ImageFlip destroyed\n");
    }

private slots:
    void imgFlipRadioButtonClicked(int flipFlagCode){
        this->flipFlagCode = flipFlagCode;
    }

private:
    int flipFlagCode = 0;

    std::vector<pair<int, QString>> flipFlagsAll =
    {
        {-99, "No flip"},
        {0, "X axis"},
        {1, "Y axis"},
        {-1, "X and Y axis"}
    };

    void initWidget()
    {
        for(unsigned int jCount = 0; jCount < flipFlagsAll.size(); jCount++)
        {
            QRadioButton *radioButton =
                    new QRadioButton(flipFlagsAll.at(jCount).second);
            if(jCount == 0)
                radioButton->setChecked(true);

            vBoxSub->addWidget(radioButton);

            connect(radioButton, &QRadioButton::clicked,
                    [=]() {
                emit imgFlipRadioButtonClicked(jCount);
            });
        }

        BaseConfigWidget::initWidget();
    }
};

#endif // IMAGEFLIP_H
