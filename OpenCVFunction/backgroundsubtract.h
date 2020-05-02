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
#include <QIntValidator>

#include "Utils/baseconfigwidget.h"
#include "CustomWidgets/errorlabel.h"

class BackgroundSubtraction : public QWidget, public BaseConfigWidget
{
    Q_OBJECT
public:
    BackgroundSubtraction()
    {
        operationName = "Blur";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#blur";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat outputImage;

        if((begin.x < kSize.width && begin.y < kSize.height)
                && (kSize.width > 0 && kSize.height > 0))
        {
            QString currentAnchorText = QString::number(begin.x)
                    + ", " + QString::number(begin.y);

            if(currentAnchorLabel->text() != currentAnchorText)
                currentAnchorLabel->setText(currentAnchorText);

            errorLabel->hide();

            pKNN->apply(inputImage, outputImage, 0.00000001);
            cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
            morphologyEx(outputImage, outputImage, CV_MOP_OPEN, element);

            cv::cvtColor(outputImage, outputImage, cv::COLOR_GRAY2BGR);
            return outputImage;
        }
        else
        {
            errorLabel->show();
            errorLabel->setText("Kernel Size should be < Anchor");
            if(kSize.width <= 0 || kSize.height <= 0)
                errorLabel->setText("Kernel Size should not be <= 0");
            return inputImage;
        }


    }

    ~BackgroundSubtraction()
    {
        printf("Blur destroyed\n");
    }

private slots:
    void applyKernelClicked(){
        kSize = cv::Size(kSizexEdit->text().toInt(),
                         kSizeyEdit->text().toInt());
    }

    void resetAnchorClicked(){
        begin = cv::Point(-1, -1);
    }

private:

    cv::Ptr< cv::BackgroundSubtractor> pMOG; //MOG Background subtractor
    cv::Ptr< cv::BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
    cv::Ptr< cv::BackgroundSubtractor> pGMG; //GMG Background subtractor
    cv::Ptr< cv::BackgroundSubtractor> pKNN; //KNN Background subtractor

    cv::Size kSize = cv::Size(101, 101);
    const int lineEditW = 50;

    QLabel* kSizeLabel  = new QLabel("Kernel Size");
    QLabel* boLabel  = new QLabel(" ( ");
    QLineEdit* kSizexEdit = new QLineEdit();
    QLabel* cmLabel  = new QLabel(" , ");
    QLineEdit* kSizeyEdit = new QLineEdit();
    QLabel* bcLabel  = new QLabel(" ) ");

    QLabel* anchorLabel  = new QLabel("Current Anchor");
    QLineEdit* currentAnchorLabel  = new QLineEdit("Default = (-1, -1)");
    QLabel* anchorNoteLabel  = new QLabel("Click on Output to select Anchor");

    QPushButton* applyButton = new QPushButton("Apply Kernel");
    QPushButton* resetAnchorButton = new QPushButton("Reset Anchor Position");

    ErrorLabel* errorLabel  = new ErrorLabel("No \nError");

    void initWidget()
    {
        pKNN = cv::createBackgroundSubtractorKNN(1,2000.0,false); //int history=500, double dist2Threshold=400.0, bool detectShadows=true

        currentAnchorLabel->setReadOnly(true);

        kSizexEdit->setText(QString::number(kSize.width));
        kSizeyEdit->setText(QString::number(kSize.height));

        errorLabel->hide();

        applyButton->setFixedWidth(200);
        resetAnchorButton->setFixedWidth(220);

        currentAnchorLabel->setAlignment(Qt::AlignCenter);
        QVBoxLayout* vboxBlurMain = new QVBoxLayout;
        vboxBlurMain->setAlignment(Qt::AlignCenter);
        vboxBlurMain->setSpacing(15);

        QFont font = anchorNoteLabel->font();
        font.setPointSize(8);
        anchorNoteLabel->setFont(font);
        anchorNoteLabel->setAlignment(Qt::AlignCenter);

        kSizexEdit->setValidator( new QIntValidator());

        kSizexEdit->setFixedWidth(lineEditW);
        kSizeyEdit->setFixedWidth(lineEditW);

        QHBoxLayout* kSizeHBox = new QHBoxLayout;
        kSizeHBox->setSpacing(10);

        kSizeHBox->addWidget(kSizeLabel);
        kSizeHBox->addWidget(boLabel);
        kSizeHBox->addWidget(kSizexEdit);
        kSizeHBox->addWidget(cmLabel);
        kSizeHBox->addWidget(kSizeyEdit);
        kSizeHBox->addWidget(bcLabel);

        QVBoxLayout* kSizeMainVBox = new QVBoxLayout;
        kSizeMainVBox->setAlignment(Qt::AlignHCenter);
        kSizeMainVBox->addLayout(kSizeHBox);
        vboxBlurMain->addLayout(kSizeMainVBox);

        QHBoxLayout* applyButtonHBox = new QHBoxLayout;
        applyButtonHBox->setAlignment(Qt::AlignHCenter);
        applyButtonHBox->addWidget(applyButton);
        vboxBlurMain->addLayout(applyButtonHBox);
        connect(applyButton, SIGNAL(released()),
                this, SLOT(applyKernelClicked()));


        QVBoxLayout* anchorMainVBox = new QVBoxLayout;
        anchorMainVBox->setAlignment(Qt::AlignHCenter);
        QHBoxLayout* anchorHBox = new QHBoxLayout;
        anchorHBox->addWidget(anchorLabel);
        anchorHBox->addWidget(currentAnchorLabel);
        anchorMainVBox->addLayout(anchorHBox);
        anchorMainVBox->addWidget(anchorNoteLabel);
        vboxBlurMain->addLayout(anchorMainVBox);

        QHBoxLayout* resetAnchorHBox = new QHBoxLayout;
        resetAnchorHBox->setAlignment(Qt::AlignHCenter);
        resetAnchorHBox->addWidget(resetAnchorButton);
        vboxBlurMain->addLayout(resetAnchorHBox);
        connect(resetAnchorButton, SIGNAL(released()),
                this, SLOT(resetAnchorClicked()));

        vboxBlurMain->addWidget(errorLabel);

        vBoxSub->addLayout(vboxBlurMain);

        BaseConfigWidget::initWidget();
    }
};

#endif // BACKGROUNDSUBTRACT_H
