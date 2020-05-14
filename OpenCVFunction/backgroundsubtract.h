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
#include <QRegExpValidator>

#include "Utils/constants.h"

#include <opencv2/bgsegm.hpp>

#include "Utils/baseconfigwidget.h"
#include "CustomWidgets/errorlabel.h"
#include "CustomWidgets/lineeditlayout.h"

class BackgroundSubtraction : public QWidget, public BaseConfigWidget
{
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

        switch (selectedTech) {
        case KNN:
            pKNN->apply(inputImage, outputImage, learningRate);
            break;
        case MOG:
            pMOG->apply(inputImage, outputImage, learningRate);
            break;
        case MOG2:
            pMOG2->apply(inputImage, outputImage, learningRate);
            break;
        case GMG:
            pGMG->apply(inputImage, outputImage, learningRate);
            break;
        case GSOC:
            pGSOC->apply(inputImage, outputImage, learningRate);
            break;
        case CNT:
            pCNT->apply(inputImage, outputImage, learningRate);
            break;
        case LSBP:
            pLSBP->apply(inputImage, outputImage, learningRate);
            break;
        }

        cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
        morphologyEx(outputImage, outputImage, cv::MORPH_OPEN, element);

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

    void applyChangesClicked(){
        learningRate = learningRateEditLayout->getText().toDouble();
    }

    void resetChangesClicked(){
        learningRate = 0.1;
        learningRateEditLayout->setText(QString::number(learningRate));
    }

    void resetAnchorClicked(){
        begin = cv::Point(-1, -1);
    }

private:
    enum MotionSubtractionTypes{
        KNN, MOG, MOG2, GMG, GSOC, CNT, LSBP
        /* More at: https://docs.opencv.org/3.4/d7/df6/classcv_1_1BackgroundSubtractor.html */
    };

    cv::Ptr< cv::BackgroundSubtractor> pMOG;
    cv::Ptr< cv::BackgroundSubtractor> pMOG2;
    cv::Ptr< cv::BackgroundSubtractor> pGMG;
    cv::Ptr< cv::BackgroundSubtractor> pKNN;
    cv::Ptr< cv::BackgroundSubtractor> pGSOC;
    cv::Ptr< cv::BackgroundSubtractor> pCNT;
    cv::Ptr< cv::BackgroundSubtractor> pLSBP;

    std::vector<QString> bkgSubTechs =
    {
        {GET_VARIABLE_NAME(KNN)},
        {GET_VARIABLE_NAME(MOG)},
        {GET_VARIABLE_NAME(MOG2)},
        {GET_VARIABLE_NAME(GMG)},
        {GET_VARIABLE_NAME(GSOC)},
        {GET_VARIABLE_NAME(CNT)},
        {GET_VARIABLE_NAME(LSBP)},
    };

    int selectedTech = KNN;

    double learningRate = 0.1;
    LineEditLayout* learningRateEditLayout  = new LineEditLayout("Learning Rate\n[0-1]",
                                                                 learningRate,
                                                                 150,
                                                                 150);
    QPushButton* applyButton = new QPushButton("Apply");
    QPushButton* resetButton = new QPushButton("Reset");

    void initWidget()
    {
        learningRateEditLayout->lineEdit->setValidator(
                    new QRegExpValidator(RegExps::regEx0_1Decimal));

        pKNN = cv::createBackgroundSubtractorKNN(1,2000.0,false); //int history=500, double dist2Threshold=400.0, bool detectShadows=true
        pMOG =  cv::bgsegm::createBackgroundSubtractorMOG();
        pMOG2 = cv::createBackgroundSubtractorMOG2();
        pGMG = cv::bgsegm::createBackgroundSubtractorGMG();
        pGSOC = cv::bgsegm::createBackgroundSubtractorGSOC();
        pCNT = cv::bgsegm::createBackgroundSubtractorCNT();
        pLSBP = cv::bgsegm::createBackgroundSubtractorLSBP();

        for(unsigned int jCount = 0; jCount < bkgSubTechs.size(); jCount++)
        {
            QRadioButton *radioButton =
                    new QRadioButton(bkgSubTechs[jCount]);
            if(jCount == 0)
                radioButton->setChecked(true);

            vBoxSub->addWidget(radioButton);

            connect(radioButton, &QRadioButton::clicked, this,
                    [=]() {
                bkgSubTechChanged(jCount);
            });
        }

        vBoxSub->addLayout(learningRateEditLayout);

        QHBoxLayout* applyButtonHBox = new QHBoxLayout;
        applyButtonHBox->setAlignment(Qt::AlignHCenter);
        applyButtonHBox->addWidget(applyButton);
        applyButtonHBox->addWidget(resetButton);
        vBoxSub->addLayout(applyButtonHBox);
        connect(applyButton, SIGNAL(released()),
                this, SLOT(applyChangesClicked()));
        connect(resetButton, SIGNAL(released()),
                this, SLOT(resetChangesClicked()));

        BaseConfigWidget::initWidget();
    }
};

#endif // BACKGROUNDSUBTRACT_H
