/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// OpenCV Color Spaces class
#ifndef COLORSPACES_H
#define COLORSPACES_H

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
#include <QThread>
#include <QSizePolicy>
#include <QSpacerItem>

#include <iostream>

using namespace cv;
using namespace std;

class ColorSpace : public QWidget, public BaseConfigWidget
{
    Q_OBJECT
public:
    ColorSpace()
    {
        operationName = "Color Space Conversion";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html#cvtcolor";
        initWidget();
    }

    Mat getProcessedImage(Mat inputImage)
    {
        Mat outputImage;
        int selectedColorCode = colorCodesAll[colorConvCode];

        // If RGB is selected: o/p = i/p
        if(selectedColorCode == -1)
            return inputImage;
        else
            cvtColor(inputImage, outputImage, selectedColorCode);

        return outputImage;
    }

    ~ColorSpace()
    {
        printf("Colorspace destroyed\n");
    }

private slots:
    void colorConvRadioButtonClicked(int colorConvCode){
        this->colorConvCode = colorConvCode;
        cout << "Stage 1: Color Code = " << colorConvCode << endl;
    }

private:
    const String rgb = "RGB";
    const String lab = "LAB";
    const String yCrCb = "YCrCb";
    const String hsv = "HSV";

    std::vector<int> colorCodesAll = {-1, CV_BGR2Lab, CV_BGR2YCrCb, CV_BGR2HSV};

    int colorConvCode = 0;

    void initWidget()
    {
        std::vector<String> colorSpacesNames = {rgb, lab, yCrCb, hsv};

        for(int jCount = 0; jCount < colorSpacesNames.size(); jCount++)
        {
            QRadioButton *radioButton = new QRadioButton(QString::fromStdString(colorSpacesNames[jCount]));
            if(jCount == 0)
                radioButton->setChecked(true);

            vBoxSub->addWidget(radioButton);

            connect(radioButton, &QRadioButton::clicked,
                    [=]() {
                emit colorConvRadioButtonClicked(jCount);
            });
        }

        BaseConfigWidget::initWidget();
    }
};

#endif // COLORSPACES_H
