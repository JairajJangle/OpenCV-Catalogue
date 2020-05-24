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
#include "CustomWidgets/sliderlayout.h"

#include "hybridslider.h"

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

        cvtColor(inputImage, outputImage, cv::COLOR_BGR2GRAY);

        if(enableBlurCB->isChecked())
            blur( outputImage, outputImage, cv::Size(3,3));

        Canny(outputImage, outputImage, t1Value, t1Value*t2Value, appertureValue);
        cvtColor(outputImage, outputImage, cv::COLOR_GRAY2BGR);

        return outputImage;
    }

    ~CannyEdge()
    {
        printf("Canny Edge destroyed\n");
    }

private slots:
    void t1ValueChanged(int value){
        t1Value = value;
    }

    void t2ValueChanged(int value){
        t2Value = value;
    }

    void appertureValueChanged(int){
        appertureValue = appertureComboBox->currentText().toInt();
        printf("Apperture: %d", appertureValue);
    }
    void testSliderValChanged(int value){
        printf("Test: %d", value);
    }
    void refreshLayout()
    {
        wgtMain->adjustSize();
    }

private:
    int t1Value = 30;
    int t2Value = 3;
    int appertureValue = 3;

    QComboBox* appertureComboBox = new QComboBox();
    QCheckBox* enableBlurCB = new QCheckBox("Enable Blur");

    void initWidget()
    {
        QHBoxLayout* t1HBox = new QHBoxLayout;
        t1HBox->setSpacing(15);

        SliderLayout* t1SliderLayout = new SliderLayout("threshold1\n[0-100]", t1Value);
        connect(t1SliderLayout, SIGNAL(sliderValueChanged(int)),
                this, SLOT(t1ValueChanged(int)));

        SliderLayout* t2SliderLayout = new SliderLayout("threshold2\n[0-100]", t2Value);
        connect(t2SliderLayout, SIGNAL(sliderValueChanged(int)),
                this, SLOT(t2ValueChanged(int)));

        QLabel* appertureLabel  = new QLabel("Apperture Value");

        QHBoxLayout* aprtHBox = new QHBoxLayout;
        aprtHBox->addWidget(appertureLabel);
        aprtHBox->setSpacing(30);
        appertureComboBox->addItems({"3", "5", "7"});
        appertureComboBox->setFixedWidth(50);
        connect(appertureComboBox,SIGNAL(activated(int)),this,SLOT(appertureValueChanged(int)));

        aprtHBox->addWidget(appertureComboBox);
        aprtHBox->insertStretch( -1, 1 );

        vBoxSub->addLayout(t1SliderLayout);
        vBoxSub->addLayout(t2SliderLayout);
        vBoxSub->addLayout(aprtHBox);

        // FIXME: Range Box hiding causes Hybrid Slider to retain height
        //        HybridSlider* hybridGG = new HybridSlider(this, "threshold1", t1Value, 0, 100);
        //        connect(hybridGG, SIGNAL(sliderValueChanged(int)),
        //                this, SLOT(t1ValueChanged(int)));
        //        connect(hybridGG, SIGNAL(editApplyClicked()),
        //                this, SLOT(refreshLayout()));

        //        vBoxSub->addWidget(hybridGG);

        connect(appertureComboBox,SIGNAL(activated(int)),this,SLOT(appertureValueChanged(int)));

        vBoxSub->addWidget(enableBlurCB);

        BaseConfigWidget::initWidget();
    }
};

#endif // CANNYEDGE_H
