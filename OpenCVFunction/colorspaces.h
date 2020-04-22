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

class ColorSpace : public QThread, public BaseConfigWidget
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
        int selectedColorCode = colorCodes[colorConvCodeStage1];

        if(selectedColorCode == -1)
            return inputImage;
        else
            cvtColor(inputImage, outputImage, selectedColorCode);

        return outputImage;
    }

    ~ColorSpace()
    {
        printf("Colorspace deleted\n");
    }

private slots:
    void colorConvRadioButtonClicked(int colorConvCode){
        colorConvCodeStage1 = colorConvCode;
        cout << "Stage 1: Color Code = " << colorConvCode << endl;
    }

private:
    const String rgb = "RGB";
    const String lab = "LAB";
    const String yCrCb = "YCrCb";
    const String hsv = "HSV";

    QWidget *wgtSub = new QWidget();

    int colorConvCodeStage1 = 0;
    int colorConvCodeStage2 = 0;

    std::vector<int> colorCodes = {-1, CV_BGR2Lab, CV_BGR2YCrCb, CV_BGR2HSV};

    void initWidget()
    {
        QScrollArea *scrl = new QScrollArea();
        QWidget *wgtMain = new QWidget();

        QVBoxLayout *vboxMain = new QVBoxLayout(wgtMain);

        QVBoxLayout *vboxSubStage1 = new QVBoxLayout(wgtSub);

        string colorSpaces[] = {rgb, lab, yCrCb, hsv};

        for(int jCount = 0; jCount <= colorSpaces->length(); jCount++)
        {
            QRadioButton *radioButton = new QRadioButton(QString::fromStdString(colorSpaces[jCount]));
            if(jCount == 0)
                radioButton->setChecked(true);

            vboxSubStage1->addWidget(radioButton);

            connect(radioButton, &QRadioButton::clicked,
                    [=]() {
                emit colorConvRadioButtonClicked(jCount);
            });
        }

        vboxMain->addWidget(wgtSub);

        scrl->setWidget(wgtMain);

        configWidget = scrl;
    }
};

#endif // COLORSPACES_H
