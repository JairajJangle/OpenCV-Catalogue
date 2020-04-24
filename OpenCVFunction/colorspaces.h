/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// OpenCV Color Spaces class
#ifndef COLORSPACES_H
#define COLORSPACES_H

// QT libs
#include <QRadioButton>

#include "Utils/baseconfigwidget.h"

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

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat outputImage;
        int selectedColorCode = colorCodesAll.at(colorConvCode).first;

        // If RGB is selected: o/p = i/p
        if(selectedColorCode == -1)
            return inputImage;
        else
        {
            cvtColor(inputImage, outputImage, selectedColorCode);
            /* As Grayscale is single channel
             * Converting to 3 channel matrix is
             * important to display as QPixMap in QLabel
             */
            if(selectedColorCode == CV_BGR2GRAY)
                cvtColor(outputImage, outputImage, CV_GRAY2BGR);
        }

        return outputImage;
    }

    ~ColorSpace()
    {
        printf("Colorspace destroyed\n");
    }

private slots:
    void colorConvRadioButtonClicked(int colorConvCode){
        this->colorConvCode = colorConvCode;
    }

private:
    std::vector<std::pair<int, QString>> colorCodesAll =
    {
        {-1, "RGB"},
        {CV_BGR2HSV, "HSV"},
        {CV_BGR2GRAY, "Grayscale"},
        {CV_BGR2Lab, "LAB"},
        {CV_BGR2YCrCb, "YCrCb"},
        {CV_BGR2Luv, "Luv"},
        {CV_BGR2HLS, "HLS"},
        {CV_BGR2XYZ, "XYZ"},
        {CV_BGR2YUV, "YUV"}
    };

    int colorConvCode = 0;

    void initWidget()
    {
        for(unsigned int jCount = 0; jCount < colorCodesAll.size(); jCount++)
        {
            QRadioButton *radioButton =
                    new QRadioButton(colorCodesAll[jCount].second);
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
