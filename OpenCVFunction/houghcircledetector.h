#ifndef HOUGHCIRCLEDETECTOR_H
#define HOUGHCIRCLEDETECTOR_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

#include "Utils/baseconfigwidget.h"
#include "CustomWidgets/sliderlayout.h"
#include "CustomWidgets/lineeditlayout.h"

#include "Utils/constants.h"

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

        if(enableBlurCB->isChecked() && blurKernelSize > 0)
            blur(grayImage, grayImage, cv::Size(blurKernelSize, blurKernelSize));

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

private slots:
    void blurKernelChanged(int value){
        blurKernelSize = value;
    }

    void blurCBClicked(bool isChecked){
        isBlurEnabled = isChecked;

        blurKernelSliderLayout->setVisible(isChecked);
    }

private:
    int blurKernelSize = 3;
    bool isBlurEnabled = true;
    QCheckBox* enableBlurCB = new QCheckBox("Enable Blur");
    SliderLayout* blurKernelSliderLayout = new SliderLayout("Blur kernel\nsize", blurKernelSize);

    int dp = 1;

    QComboBox* selectMethodComboBox = new QComboBox();
    LineEditLayout* dpLineEditLayout = new LineEditLayout("dp", dp);

    void initWidget()
    {
        dpLineEditLayout->lineEdit->setValidator(new QRegExpValidator(RegExps::regExInt_greaterThan0));

        enableBlurCB->setChecked(true);
        connect(enableBlurCB, SIGNAL(clicked(bool)), this, SLOT(blurCBClicked(bool)));
        connect(blurKernelSliderLayout, SIGNAL(sliderValueChanged(int)),
                this, SLOT(blurKernelChanged(int)));

        QLabel* selectMethodLabel = new QLabel("Select Method");
        selectMethodComboBox->addItem("CV_HOUGH_GRADIENT");
        QHBoxLayout* selectMethodHBox = new QHBoxLayout;
        selectMethodHBox->addWidget(selectMethodLabel);
        selectMethodHBox->addWidget(selectMethodComboBox);
        vBoxSub->addLayout(selectMethodHBox);

        vBoxSub->addLayout(dpLineEditLayout);

        QFrame* line = new QFrame(this);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(320, 150, 118, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setFixedHeight(20);
        vBoxSub->addWidget(line);

        // TODO: Add Hough Circles function control trackbars
        vBoxSub->addWidget(enableBlurCB);
        vBoxSub->addLayout(blurKernelSliderLayout);
        BaseConfigWidget::initWidget();
    }

};

#endif // HOUGHCIRCLEDETECTOR_H
