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
#include "CustomWidgets/labelledcombobox.h"
#include "CustomWidgets/sliderlayout.h"

class ErodeDilate : public BaseConfigWidget
{
    Q_OBJECT
public:
    enum MorphologyType{ERODE, DILATE};
    ErodeDilate(MorphologyType morphologyType): morphType(morphologyType)
    {
        operationName = morphType == DILATE ? "Dilate" : "Erode";
        moreInfoLink = morphType == DILATE ? "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#dilate"
                                           : "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#erode";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
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
                                                        cv::Point(-1, -1));

            // FIXME: Check need to customize borderValue parameter for dilate(...)
            morphType == DILATE
                    ? cv::dilate(inputImage, outputImage,
                                 element, begin, iterationCount,
                                 borderType)
                    : cv::erode(inputImage, outputImage,
                                element, begin, iterationCount,
                                borderType);

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
void morphShapeChanged(QVariant value){
    kernelMorphShape = value.toInt();
    qDebug() << "Morph Shape: " << kernelMorphShape;
}
void iterationChanged(int value){
    iterationCount = value;
}
void borderChanged(QVariant value){
    qDebug() << "Border Type: " << value;
    borderType = value.toInt();
}

private:
const int dilationSize = 6;
int kernelMorphShape = cv::MORPH_CROSS; // cv::MorphShapes
cv::Size kSize = cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1);
cv::Point kernelAnchor = cv::Point(-1, -1);
int iterationCount = 1;
int borderType = cv::BORDER_CONSTANT;
const MorphologyType morphType;

DualLineEditLayout *kSizeDLEL = new DualLineEditLayout("Kernel Size",
                                                       qMakePair(kSize.width,kSize.height),
                                                       70);

LineEditLayout* anchorLineEditLayout =
        new LineEditLayout("Current Anchor", "Default = (-1, -1)",
                           160, 150);

QString prevAnchorText = "";

ApplyResetButtonLayout* applyResetBL = new ApplyResetButtonLayout();

void initWidget() override
{
    QLabel* anchorNoteLabel  = new QLabel("Click on Output to select Anchor");

    anchorLineEditLayout->lineEdit->setReadOnly(true);

    vBoxSub->setSpacing(20);

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

    QVBoxLayout* anchorMainVBox = new QVBoxLayout;
    anchorMainVBox->setAlignment(Qt::AlignHCenter);
    anchorMainVBox->setSpacing(5);
    anchorMainVBox->addLayout(anchorLineEditLayout);
    anchorMainVBox->addWidget(anchorNoteLabel);

    QMap<QString, QVariant> morphShapeMap;
    morphShapeMap.insert("MORPH_RECT", cv::MORPH_RECT);
    morphShapeMap.insert("MORPH_CROSS", cv::MORPH_CROSS);
    morphShapeMap.insert("MORPH_ELLIPSE", cv::MORPH_ELLIPSE);

    LabelledComboBox* morphShapeLCB = new LabelledComboBox("kernelMorhShape",
                                                           morphShapeMap);
    connect(morphShapeLCB,SIGNAL(currentIndexChanged(QVariant)),
            this,SLOT(morphShapeChanged(QVariant)));
    SliderLayout* iterationCountSL = new SliderLayout("iterations", iterationCount);
    connect(iterationCountSL, SIGNAL(sliderValueChanged(int)),
            this, SLOT(iterationChanged(int)));

    QMap<QString, QVariant> borderTypes;
    borderTypes.insert("BORDER_CONSTANT", cv::BORDER_CONSTANT);
    borderTypes.insert("BORDER_REPLICATE", cv::BORDER_REPLICATE);
    borderTypes.insert("BORDER_REFLECT", cv::BORDER_REFLECT);
    /*!
         * borderTypeLCB->addItem( "BORDER_WRAP", 3);
         * BORDER_WRAP is not supported, see @var moreInfoLink page
         */
    borderTypes.insert("BORDER_DEFAULT", cv::BORDER_DEFAULT);
    borderTypes.insert("BORDER_REFLECT_101", cv::BORDER_REFLECT_101);
    /*!
         * FIXME:
         * borderTypeLCB->addItem("BORDER_TRANSPARENT", cv::BORDER_TRANSPARENT);
         * BORDER_TRANSPARENT is causing crash
         */
    borderTypes.insert("BORDER_REFLECT101", cv::BORDER_REFLECT101);
    borderTypes.insert("BORDER_ISOLATED", cv::BORDER_ISOLATED);

    LabelledComboBox* borderTypeLCB = new LabelledComboBox("borderType",
                                                           borderTypes);
    borderTypeLCB->comboBox->setCurrentText("BORDER_CONSTANT");
    connect(borderTypeLCB,SIGNAL(currentIndexChanged(QVariant)),
            this,SLOT(borderChanged(QVariant)));

    vBoxSub->addLayout(kSizeDLEL);
    vBoxSub->addLayout(applyResetBL);
    vBoxSub->addLayout(anchorMainVBox);
    vBoxSub->addLayout(morphShapeLCB);
    vBoxSub->addLayout(iterationCountSL);
    vBoxSub->addLayout(borderTypeLCB);

    // TODO: Add Config widgets
    BaseConfigWidget::initWidget();
}
};
