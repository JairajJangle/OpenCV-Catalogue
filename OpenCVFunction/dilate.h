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

#pragma once

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/duallineeditlayout.h"
#include "CustomWidgets/applyresetbuttonlayout.h"
#include "CustomWidgets/lineeditlayout.h"

class Dilate : public BaseConfigWidget
{
    Q_OBJECT
public:
    Dilate()
    {
        operationName = "Dilate";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#dilate";
        initWidget();
    }

    ~Dilate()
    {
        qDebug() << "Dilate Destroyed";
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
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

            cv::Mat outputImage;

            cv::Mat element = cv::getStructuringElement(kernelMorphShape,
                                                        kSize,
                                                        begin);

            cv::dilate(inputImage, outputImage, element);

            // dilate(inputImage, outputImage, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

            return outputImage;
        }
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

private slots:
void applyClicked(){
    kSize = cv::Size(kSizeDLEL->getTexts().first.toInt(),
                     kSizeDLEL->getTexts().second.toInt());
}
void resetClicked(){
    kSize = cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1);
}

protected:
const int dilationSize = 6;
int kernelMorphShape = cv::MORPH_CROSS; // cv::MorphShapes
cv::Size kSize = cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1);
cv::Point kernelAnchor = cv::Point(-1, -1);

DualLineEditLayout *kSizeDLEL = new DualLineEditLayout("Kernel Size",
                                                       qMakePair(kSize.width,kSize.height),
                                                       70);

LineEditLayout* anchorLineEditLayout =
        new LineEditLayout("Current Anchor", "Default = (-1, -1)",
                           160, 150);

QLabel* anchorNoteLabel  = new QLabel("Click on Output to select Anchor");
QString prevAnchorText = "";

ApplyResetButtonLayout* applyResetBL = new ApplyResetButtonLayout();

void initWidget()
{
    anchorLineEditLayout->lineEdit->setReadOnly(true);

    vBoxSub->setSpacing(15);

    QFont font = anchorNoteLabel->font();
    font.setPointSize(8);
    anchorNoteLabel->setFont(font);
    anchorNoteLabel->setAlignment(Qt::AlignCenter);

    QIntValidator* kSizeValidator = new QIntValidator();
    kSizeValidator->setBottom(1);

    kSizeDLEL->setValidator(kSizeValidator);

    connect(applyResetBL, SIGNAL(applyClicked()),
            this, SLOT(applyClicked()));
    connect(applyResetBL, SIGNAL(resetClicked()),
            this, SLOT(resetClicked()));

    vBoxSub->addLayout(kSizeDLEL);

    QVBoxLayout* anchorMainVBox = new QVBoxLayout;
    anchorMainVBox->setAlignment(Qt::AlignHCenter);
    anchorMainVBox->addLayout(anchorLineEditLayout);
    anchorMainVBox->addWidget(anchorNoteLabel);

    vBoxSub->addLayout(anchorMainVBox);
    vBoxSub->addLayout(applyResetBL);

    // TODO: Add Config widgets
    BaseConfigWidget::initWidget();
}
};
