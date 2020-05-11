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
#include "CustomWidgets/applyresetbuttonlayout.h"

#include "Utils/constants.h"
#include "Utils/utils.h"

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

        if(minDist == -1.0)
        {
            minDist = grayImage.rows/8;
            minDistLayout->lineEdit->setText(QString::number(minDist));
        }

        if(enableBlurCB->isChecked() && blurKernelSize > 0)
            blur(grayImage, grayImage, cv::Size(blurKernelSize, blurKernelSize));

        std::vector<cv::Vec3f> circles;

        /// Apply the Hough Transform to find the circles
        HoughCircles(grayImage, circles, CV_HOUGH_GRADIENT,
                     dp, minDist, 200, 100, 0, 0 );

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

    void applyClicked(){
        QString text = dpLineEditLayout->getText();
        if(dpLineEditLayout->getText().isEmpty())
        {
            dp = 1;
            dpLineEditLayout->lineEdit->setText(QString::number(dp));
        }
        else
        {
            dp = text.toInt();
        }

        dp = dpLineEditLayout->getText().toInt();
        minDist = minDistLayout->getText().toDouble();
        param1 = param1Layout->getText().toDouble();
        param2= param2Layout->getText().toDouble();
        minRadius = minRadiusLayout->getText().toInt();
        maxRadius = maxRadiusLayout->getText().toInt();
    }

    void resetClicked(){
        dp = 1;
        minDist = -1.0;
        param1 = 100.0;
        param2 = 100.0;
        minRadius = 0;
        maxRadius = 0;

        dpLineEditLayout->setText(dp);
        minDistLayout->setText(minDist);
        param1Layout->setText(param1);
        param2Layout->setText(param2);
        minRadiusLayout->setText(minRadius);
        maxRadiusLayout->setText(maxRadius);
    }

private:
    int blurKernelSize = 3;
    bool isBlurEnabled = true;
    QCheckBox* enableBlurCB = new QCheckBox("Enable Blur");
    SliderLayout* blurKernelSliderLayout = new SliderLayout("Blur kernel\nsize", blurKernelSize);

    int dp = 1;
    double minDist = -1.0;
    double param1 = 100.0;
    double param2 = 100.0;
    int minRadius = 0;
    int maxRadius = 0;

    QDoubleValidator* minDistValidator = new QDoubleValidator();

    QComboBox* selectMethodComboBox = new QComboBox();

    LineEditLayout* dpLineEditLayout = new LineEditLayout("dp", QString::number(dp));
    LineEditLayout* minDistLayout = new LineEditLayout("minDist", "NA");
    LineEditLayout* param1Layout = new LineEditLayout("param1", QString::number(param1));
    LineEditLayout* param2Layout = new LineEditLayout("param2", QString::number(param2));
    LineEditLayout* minRadiusLayout = new LineEditLayout("minRadius", QString::number(minRadius));
    LineEditLayout* maxRadiusLayout = new LineEditLayout("maxRadius", QString::number(maxRadius));

    // TODO: Reduce code length with dynamic get and set values in line Edits
    std::vector<std::pair<LineEditLayout*, Unions::Numeric>> lineEditsWithParams;

    ApplyResetButtonLayout* applyResetBox = new ApplyResetButtonLayout();

    void initWidget()
    {
        minDistValidator->setBottom(0);
        minDistValidator->setDecimals(2);

        QIntValidator* dpValidator = new QIntValidator();
        dpValidator->setBottom(0);
        dpLineEditLayout->lineEdit->setValidator(dpValidator);
        minDistLayout->lineEdit->setValidator(minDistValidator);
        // TODO: Add validators to other fields if required

        enableBlurCB->setChecked(true);
        connect(enableBlurCB, SIGNAL(clicked(bool)),
                this, SLOT(blurCBClicked(bool)));
        connect(blurKernelSliderLayout, SIGNAL(sliderValueChanged(int)),
                this, SLOT(blurKernelChanged(int)));

        connect(applyResetBox, SIGNAL(applyClicked()),
                this, SLOT(applyClicked()));
        connect(applyResetBox, SIGNAL(resetClicked()),
                this, SLOT(resetClicked()));

        QLabel* selectMethodLabel = new QLabel("Select Method");
        selectMethodComboBox->addItem("CV_HOUGH_GRADIENT");
        QHBoxLayout* selectMethodHBox = new QHBoxLayout;
        selectMethodHBox->addWidget(selectMethodLabel);
        selectMethodHBox->addWidget(selectMethodComboBox);
        vBoxSub->addLayout(selectMethodHBox);

        vBoxSub->addLayout(dpLineEditLayout);
        vBoxSub->addLayout(minDistLayout);
        vBoxSub->addLayout(param1Layout);
        vBoxSub->addLayout(param2Layout);
        vBoxSub->addLayout(minRadiusLayout);
        vBoxSub->addLayout(maxRadiusLayout);

        // TODO get click signal from Apply Reset Buttons
        vBoxSub->addLayout(applyResetBox);

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
