#ifndef COLORPICKER_H
#define COLORPICKER_H


/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/lineeditlayout.h"
#include "Utils/baseconfigwidget.h"

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

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat outputImage;

        // If No Location is selected: o/p = 0
        if(begin ==cv::Point(-1, -1))
            return inputImage;
        else
        {
            QString locationValues =
                    QString::number(begin.x) + ", "
                    +  QString::number(begin.y);

            locLineEditLayout->setText(locationValues);

            cv::Vec3b color = inputImage.at<cv::Vec3b>(begin);

            QString rgbValues =
                    QString::number(color[0]) + ", "
                    +  QString::number(color[1]) + ", "
                    +  QString::number(color[2]);

            rgbLineEditLayout->setText(rgbValues);
        }

        begin =cv::Point(-1, -1);

        return inputImage;
    }

    ~ColorPicker()
    {
        printf("Color Picker destroyed\n");
    }

private:
    LineEditLayout* rgbLineEditLayout = new LineEditLayout("RGB", "000, 000, 000", 200);

    LineEditLayout* locLineEditLayout = new LineEditLayout("Location", "No location selected", 200);

    QLabel* infoLabel  = new QLabel("Click on Output feed to pick color\n");

    void initWidget()
    {
        locLineEditLayout->lineEdit->setReadOnly(true);
        vBoxSub->addWidget(infoLabel);

        vBoxSub->addLayout(rgbLineEditLayout);
        vBoxSub->addLayout(locLineEditLayout);

        BaseConfigWidget::initWidget();
    }
};


#endif // COLORPICKER_H
