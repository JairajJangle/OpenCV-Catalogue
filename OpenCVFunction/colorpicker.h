#ifndef COLORPICKER_H
#define COLORPICKER_H


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
#include <QThread>
#include <QSizePolicy>
#include <QLineEdit>

#include <iostream>

using namespace cv;
using namespace std;

class ColorPicker : public QWidget, public BaseConfigWidget
{
    Q_OBJECT
public:
    ColorPicker()
    {
        operationName = "Color Picker";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat-at";
        initWidget();
    }

    Mat getProcessedImage(Mat inputImage)
    {
        Mat outputImage;

        // If No Location is selected: o/p = 0
        if(begin == Point(-1, -1))
            return inputImage;
        else
        {
            QString locationValues =
                    QString::number(begin.x) + ", "
                    +  QString::number(begin.y);

            locLabel->setText(locationValues);

            Vec3b color = inputImage.at<Vec3b>(begin);

            QString rgbValues =
                    QString::number(color[0]) + ", "
                    +  QString::number(color[1]) + ", "
                    +  QString::number(color[2]);

            rgbLabel->setText(rgbValues);
        }

        begin = Point(-1, -1);

        return inputImage;
    }

    ~ColorPicker()
    {
        printf("Color Picker destroyed\n");
    }

private:
    QLineEdit* rgbLabel  = new QLineEdit("000, 000, 000");
    QLineEdit* locLabel  = new QLineEdit("No location selected");

    QLabel* infoLabel  = new QLabel("Click on Output feed to pick color\n");

    void initWidget()
    {
        vBoxSub->addWidget(infoLabel);

        rgbLabel->setAlignment(Qt::AlignCenter);
        locLabel->setAlignment(Qt::AlignCenter);

        QHBoxLayout* rgbHBox = new QHBoxLayout;

        rgbHBox->addWidget(new QLabel("RGB: "));
        rgbHBox->addWidget(rgbLabel);

        vBoxSub->addLayout(rgbHBox);

        QHBoxLayout* locHBox = new QHBoxLayout;

        locHBox->addWidget(new QLabel("Location: "));
        locHBox->addWidget(locLabel);

        vBoxSub->addLayout(locHBox);

        BaseConfigWidget::initWidget();
    }
};


#endif // COLORPICKER_H
