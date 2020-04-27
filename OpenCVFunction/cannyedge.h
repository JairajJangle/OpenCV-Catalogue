#ifndef CANNYEDGE_H
#define CANNYEDGE_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>

#include "Utils/baseconfigwidget.h"

class CannyEdge : public QWidget, public BaseConfigWidget
{
    Q_OBJECT
public:
    CannyEdge()
    {
        operationName = "Canny Edge";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=canny#canny";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat outputImage;

        cvtColor(inputImage, outputImage, CV_BGR2GRAY);

        if(enableBlurCB->isChecked())
            blur( outputImage, outputImage, cv::Size(3,3));

        Canny(outputImage, outputImage, t1Value, t1Value*t2Value, appertureValue);
        cvtColor(outputImage, outputImage, CV_GRAY2BGR);

        return outputImage;
    }

    ~CannyEdge()
    {
        printf("Canny Edge destroyed\n");
    }

private slots:
    void tiValueChanged(int value){
        t1Value = value;
        t1ValueLabel->setText(QString::number(t1Value));
    }

    void t2ValueChanged(int value){
        t2Value = value;
        t2ValueLabel->setText(QString::number(t2Value));
    }

    void appertureValueChanged(int){
        appertureValue = appertureComboBox->currentText().toInt();
        printf("Apperture: %d", appertureValue);
    }

private:
    int t1Value = 30;
    int t2Value = 3;
    int appertureValue = 3;

    QLabel* t1ValueLabel  = new QLabel("0");
    QLabel* t2ValueLabel  = new QLabel("0");
    QComboBox* appertureComboBox = new QComboBox();
    QCheckBox* enableBlurCB = new QCheckBox("Enable Blue");

    void initWidget()
    {
        QLabel* t1Label  = new QLabel("threshold1\n[0-100]");
        QLabel* t2Label  = new QLabel("threshold2\n[0-100]");

        t1ValueLabel->setFixedSize(40, 20);
        t2ValueLabel->setFixedSize(40, 20);

        QHBoxLayout* t1HBox = new QHBoxLayout;
        t1HBox->setSpacing(15);

        QSlider* t1Slider = new QSlider();
        t1Slider->setFixedSize(160, 50);
        t1Slider->setSingleStep(20);
        t1Slider->setOrientation(Qt::Horizontal);
        t1Slider->setRange(0, 100);
        t1Slider->setValue(t1Value);

        t1HBox->addWidget(t1Label);
        t1HBox->addWidget(t1Slider);
        t1HBox->addWidget(t1ValueLabel);

        connect(t1Slider, SIGNAL(valueChanged(int)),this, SLOT(tiValueChanged(int)));

        QHBoxLayout* t2HBox = new QHBoxLayout;
        t2HBox->setSpacing(15);

        QSlider* t2Slider = new QSlider();
        t2Slider->setFixedSize(160, 50);
        t2Slider->setSingleStep(20);
        t2Slider->setOrientation(Qt::Horizontal);
        t2Slider->setRange(0, 100);
        t2Slider->setValue(t2Value);

        t2HBox->addWidget(t2Label);
        t2HBox->addWidget(t2Slider);
        t2HBox->addWidget(t2ValueLabel);

        connect(t2Slider, SIGNAL(valueChanged(int)),this, SLOT(t2ValueChanged(int)));

        QLabel* appertureLabel  = new QLabel("Apperture Value");

        QHBoxLayout* aprtHBox = new QHBoxLayout;
        aprtHBox->addWidget(appertureLabel);
        aprtHBox->setSpacing(30);
        appertureComboBox->addItems({"3", "5", "7"});
        appertureComboBox->setFixedWidth(50);
        connect(appertureComboBox,SIGNAL(activated(int)),this,SLOT(appertureValueChanged(int)));

        aprtHBox->addWidget(appertureComboBox);
        aprtHBox->insertStretch( -1, 1 );

        vBoxSub->addLayout(t1HBox);
        vBoxSub->addLayout(t2HBox);
        vBoxSub->addLayout(aprtHBox);
        vBoxSub->addWidget(enableBlurCB);

        BaseConfigWidget::initWidget();
    }
};

#endif // CANNYEDGE_H
