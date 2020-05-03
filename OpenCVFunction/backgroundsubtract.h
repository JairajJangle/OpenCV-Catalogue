#ifndef BACKGROUNDSUBTRACT_H
#define BACKGROUNDSUBTRACT_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

#include "Utils/baseconfigwidget.h"
#include "CustomWidgets/errorlabel.h"

class BackgroundSubtraction : public QWidget, public BaseConfigWidget
{
#define GET_VARIABLE_NAME(Variable) (#Variable)

    Q_OBJECT
public:
    BackgroundSubtraction()
    {
        operationName = "Background Subtraction";
        moreInfoLink = "https://docs.opencv.org/3.4/d7/df6/classcv_1_1BackgroundSubtractor.html";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat outputImage;

        pKNN->apply(inputImage, outputImage, 0.00000001);
        cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
        morphologyEx(outputImage, outputImage, CV_MOP_OPEN, element);

        cv::cvtColor(outputImage, outputImage, cv::COLOR_GRAY2BGR);
        return outputImage;
    }

    ~BackgroundSubtraction()
    {
        printf("Blur destroyed\n");
    }

private slots:
    void bkgSubTechChanged(int bkgSubTech){
        selectedTech = bkgSubTech;
    }

    void resetAnchorClicked(){
        begin = cv::Point(-1, -1);
    }

private:
    enum MotionSubtractionTypes{
        KNN, MOG, MOG2, GMG
        /* More at: https://docs.opencv.org/3.4/d7/df6/classcv_1_1BackgroundSubtractor.html */
    };

    cv::Ptr< cv::BackgroundSubtractor> pMOG; //MOG Background subtractor
    cv::Ptr< cv::BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
    cv::Ptr< cv::BackgroundSubtractor> pGMG; //GMG Background subtractor
    cv::Ptr< cv::BackgroundSubtractor> pKNN; //KNN Background subtractor

    std::vector<QString> bkgSubTechs =
    {
        {GET_VARIABLE_NAME(KNN)},
        {GET_VARIABLE_NAME(MOG)},
        {GET_VARIABLE_NAME(MOG2)},
        {GET_VARIABLE_NAME(GMG)},
    };

    int selectedTech = KNN;

    void initWidget()
    {
        pKNN = cv::createBackgroundSubtractorKNN(1,2000.0,false); //int history=500, double dist2Threshold=400.0, bool detectShadows=true

        for(unsigned int jCount = 0; jCount < bkgSubTechs.size(); jCount++)
        {
            QRadioButton *radioButton =
                    new QRadioButton(bkgSubTechs[jCount]);
            if(jCount == 0)
                radioButton->setChecked(true);

            vBoxSub->addWidget(radioButton);

            connect(radioButton, &QRadioButton::clicked,
                    [=]() {
                emit bkgSubTechChanged(jCount);
            });
        }

        BaseConfigWidget::initWidget();
    }
};

#endif // BACKGROUNDSUBTRACT_H
