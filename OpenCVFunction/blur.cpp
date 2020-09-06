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

#include "OpenCVFunction/blur.h"

Blur::Blur()
{
    operationName = "Blur";
    moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#blur";
    initWidget();
}

cv::Mat Blur::getProcessedImage(cv::Mat inputImage) try
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

    //            errorLabel->show();
    //            errorLabel->setText("Kernel Size should be < Anchor");
    //            if(kSize.width <= 0 || kSize.height <= 0)
    //                errorLabel->setText("Kernel Size should not be <= 0");

    return inputImage;
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

void Blur::applyKernelClicked(){
    kSize = cv::Size(kSizeDLEL->getTexts().first.toInt(),
                     kSizeDLEL->getTexts().second.toInt());
}

void Blur::resetAnchorClicked(){
    begin = cv::Point(-1, -1);
}

void Blur::initWidget()
{
    anchorLineEditLayout->lineEdit->setReadOnly(true);

    errorLabel->hide();

    applyButton->setFixedWidth(200);
    resetAnchorButton->setFixedWidth(220);

    vBoxSub->setSpacing(15);

    QFont font = anchorNoteLabel->font();
    font.setPointSize(8);
    anchorNoteLabel->setFont(font);
    anchorNoteLabel->setAlignment(Qt::AlignCenter);

    QIntValidator* kSizeValidator = new QIntValidator();
    kSizeValidator->setBottom(1);

    kSizeDLEL->setValidator(kSizeValidator);

    vBoxSub->addLayout(kSizeDLEL);

    QHBoxLayout* applyButtonHBox = new QHBoxLayout;
    applyButtonHBox->setAlignment(Qt::AlignHCenter);
    applyButtonHBox->addWidget(applyButton);
    vBoxSub->addLayout(applyButtonHBox);
    connect(applyButton, SIGNAL(released()),
            this, SLOT(applyKernelClicked()));

    QVBoxLayout* anchorMainVBox = new QVBoxLayout;
    anchorMainVBox->setAlignment(Qt::AlignHCenter);

    anchorMainVBox->addLayout(anchorLineEditLayout);
    anchorMainVBox->addWidget(anchorNoteLabel);
    anchorMainVBox->setSpacing(0);

    vBoxSub->addLayout(anchorMainVBox);

    QHBoxLayout* resetAnchorHBox = new QHBoxLayout;
    resetAnchorHBox->setAlignment(Qt::AlignHCenter);
    resetAnchorHBox->addWidget(resetAnchorButton);
    vBoxSub->addLayout(resetAnchorHBox);
    connect(resetAnchorButton, SIGNAL(released()),
            this, SLOT(resetAnchorClicked()));

    vBoxSub->addWidget(errorLabel);

    BaseConfigWidget::initWidget();
}
