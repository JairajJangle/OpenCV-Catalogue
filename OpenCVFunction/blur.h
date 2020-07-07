/* OpenCV Catalogue is a desktop GUI application to showcase some OpenCV functions
 * and parameter adjustment using controls in GUI.
 * Copyright (C) 2020  Jairaj Jangle
 *
 * This file is part of OpenCV Catalogue.
 *
 * OpenCV Catalogue is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenCV Catalogue is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenCV Catalogue.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BLUR_H
#define BLUR_H

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>

#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/errorlabel.h"

class Blur : public BaseConfigWidget
{
    Q_OBJECT
public:
    Blur()
    {
        operationName = "Blur";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#blur";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        cv::Mat outputImage;

        if((begin.x < kSize.width && begin.y < kSize.height)
                && (kSize.width > 0 && kSize.height > 0))
        {
            QString currentAnchorText = QString::number(begin.x)
                    + ", " + QString::number(begin.y);

            if(prevAnchorText != currentAnchorText)
            {
                anchorLineEditLayout->setText(currentAnchorText);
                prevAnchorText = currentAnchorText;
            }

//            errorLabel->hide();
            cv::blur(inputImage, outputImage, kSize, begin);

            return outputImage;
        }
        else
        {
//            errorLabel->show();
//            errorLabel->setText("Kernel Size should be < Anchor");
//            if(kSize.width <= 0 || kSize.height <= 0)
//                errorLabel->setText("Kernel Size should not be <= 0");

            return inputImage;
        }

    }
    catch(cv::Exception& e){
        throw e;
    } catch(std::exception& e) {
        throw e;
    }
    catch(...){
    throw std::string("Unknown Exception in ")
    + std::string(typeid(this).name());
}

    ~Blur()
    {
        qDebug() << "Blur destroyed";
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
    cv::Size kSize = cv::Size(101, 101);
    const int lineEditW = 50;

    QLabel* kSizeLabel  = new QLabel("Kernel Size");
    QLabel* boLabel  = new QLabel(" ( ");
    QLineEdit* kSizexEdit = new QLineEdit();
    QLabel* cmLabel  = new QLabel(" , ");
    QLineEdit* kSizeyEdit = new QLineEdit();
    QLabel* bcLabel  = new QLabel(" ) ");

    LineEditLayout* anchorLineEditLayout =
            new LineEditLayout("Current Anchor", "Default = (-1, -1)",
                               160, 150);

    QLabel* anchorNoteLabel  = new QLabel("Click on Output to select Anchor");

    QPushButton* applyButton = new QPushButton("Apply Kernel");
    QPushButton* resetAnchorButton = new QPushButton("Reset Anchor Position");

    ErrorLabel* errorLabel  = new ErrorLabel("No \nError");

    QString prevAnchorText = "";

    void initWidget()
    {
        anchorLineEditLayout->lineEdit->setReadOnly(true);

        kSizexEdit->setText(QString::number(kSize.width));
        kSizeyEdit->setText(QString::number(kSize.height));

        errorLabel->hide();

        applyButton->setFixedWidth(200);
        resetAnchorButton->setFixedWidth(220);

        QVBoxLayout* vboxBlurMain = new QVBoxLayout;
        vboxBlurMain->setAlignment(Qt::AlignCenter);
        vboxBlurMain->setSpacing(15);

        QFont font = anchorNoteLabel->font();
        font.setPointSize(8);
        anchorNoteLabel->setFont(font);
        anchorNoteLabel->setAlignment(Qt::AlignCenter);

        QIntValidator* kSizeValidator = new QIntValidator();
        kSizeValidator->setBottom(1);
        kSizexEdit->setValidator(kSizeValidator);

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

        anchorMainVBox->addLayout(anchorLineEditLayout);
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

#endif // BLUR_H
