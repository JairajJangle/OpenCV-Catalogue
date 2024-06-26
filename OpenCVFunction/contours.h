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

#include "CustomWidgets/baseconfigwidget.h"
#include "CustomWidgets/labelledcombobox.h"
#include "CustomWidgets/lineeditlayout.h"
#include "CustomWidgets/dividerline.h"
#include "CustomWidgets/sliderlayout.h"

class Contours : public BaseConfigWidget
{
    Q_OBJECT
public:
    Contours()
    {
        operationName = "Contours";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html#findcontours";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        if(begin.x < 0 || begin.y < 0)
            begin = cv::Point(0,0);
        QString currentOffsetText = QString::number(begin.x)
                                    + ", " + QString::number(begin.y);

        if(prevOffsetText != currentOffsetText)
        {
            offsetLEL->setText(currentOffsetText);
            prevOffsetText = currentOffsetText;
        }

        /// Find contours
        cv::findContours(inputImage, contours, hierarchy,
                         mode, method,
                         begin);

        /// Draw contours
        cv::Mat drawing = cv::Mat::zeros(inputImage.size(), CV_8UC3);
        for(unsigned int i = 0; i < contours.size(); i++)
        {
            cv::Scalar color = cv::Scalar(lineB, lineG, lineR);
            drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, begin);
        }

        return drawing;
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
    void modeChanged(int value)
    {
        mode = value;
    }
    void methodChanged(int value)
    {
        method = value;
    }

private:
    int mode = cv::RETR_TREE;
    int method = cv::CHAIN_APPROX_SIMPLE;

    LineEditLayout* offsetLEL =
        new LineEditLayout("Current Offset", "Default = (-1, -1)",
                           160, 150);
    QString prevOffsetText = "";
    QLabel* offsetNoteLabel  = new QLabel("Click on Output to select offset");

    unsigned int lineB = 0, lineG = 255, lineR = 204;

    void initWidget() override
    {
        QList<QVariant> modeList = {
            "RETR_EXTERNAL",
            "RETR_LIST",
            "RETR_CCOMP",
            "RETR_TREE",
            "RETR_FLOODFILL (CV_32SC1 only)"};

        LabelledComboBox* modeLCB = new LabelledComboBox("mode", modeList);
        connect(modeLCB, SIGNAL(currentIndexChanged(int)),
                this, SLOT(modeChanged(int)));
        modeLCB->comboBox->setCurrentIndex(mode);

        QList<QVariant> methodList = {
            "CV_CHAIN_CODE", // Crashes
            "CV_CHAIN_APPROX_NONE",
            "CV_CHAIN_APPROX_SIMPLE",
            "CV_CHAIN_APPROX_TC89_L1",
            "CV_CHAIN_APPROX_TC89_KCOS",
            "CV_LINK_RUNS"}; // Crashes

        LabelledComboBox* methodLCB = new LabelledComboBox("method", methodList);
        connect(methodLCB, SIGNAL(currentIndexChanged(int)),
                this, SLOT(methodChanged(int)));
        methodLCB->comboBox->setCurrentIndex(method);

        QVBoxLayout* offsetMainVBox = new QVBoxLayout;
        offsetMainVBox->setAlignment(Qt::AlignHCenter);

        offsetLEL->lineEdit->setReadOnly(true);
        offsetMainVBox->addLayout(offsetLEL);
        offsetMainVBox->setSpacing(0);

        QFont font = offsetNoteLabel->font();
        font.setPointSize(8);
        offsetNoteLabel->setFont(font);
        offsetNoteLabel->setAlignment(Qt::AlignCenter);
        offsetMainVBox->addWidget(offsetNoteLabel);

        QVBoxLayout* lineColorsMainLayout = new QVBoxLayout();
        QHBoxLayout* lineColorsLayout = new QHBoxLayout();
        SliderLayout* bSL = new SliderLayout("B", lineB, 0, 255, 60);
        SliderLayout* gSL = new SliderLayout("G", lineG, 0, 255, 60);
        SliderLayout* rSL = new SliderLayout("R", lineR, 0, 255, 60);
        connect(bSL, &SliderLayout::sliderValueChanged,
                this, [=](int value){lineB = value;});
        connect(gSL, &SliderLayout::sliderValueChanged,
                this, [=](int value){lineG = value;});
        connect(rSL, &SliderLayout::sliderValueChanged,
                this, [=](int value){lineR = value;});
        bSL->setSpacing(5); gSL->setSpacing(5); rSL->setSpacing(5);
        lineColorsLayout->setSpacing(5);
        lineColorsLayout->addLayout(bSL);
        lineColorsLayout->addLayout(gSL);
        lineColorsLayout->addLayout(rSL);

        lineColorsMainLayout->addWidget(new QLabel("Contour Line"));
        lineColorsMainLayout->addLayout(lineColorsLayout);
        lineColorsMainLayout->setSpacing(2);

        vBoxSub->setSpacing(25);
        vBoxSub->addLayout(modeLCB);
        vBoxSub->addLayout(methodLCB);
        vBoxSub->addLayout(offsetMainVBox);
        vBoxSub->addWidget(new DividerLine(1));
        vBoxSub->addLayout(lineColorsMainLayout);

        BaseConfigWidget::initWidget();
    }
};
