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
#include "CustomWidgets/sliderlayout.h"
#include "CustomWidgets/labelledcombobox.h"
#include "CustomWidgets/HybridSlider/hybridslider.h"

class CannyEdge : public BaseConfigWidget
{
    Q_OBJECT
public:
    CannyEdge()
    {
        operationName = "Canny Edge";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=canny#canny";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        cv::Mat outputImage;

        cvtColor(inputImage, outputImage, cv::COLOR_BGR2GRAY);

        Canny(outputImage, outputImage, t1Value, t1Value*t2Value, appertureValue);

        return outputImage;
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

~CannyEdge()
{
    qDebug() << "Canny Edge destroyed";
}

private slots:
void t1ValueChanged(int value){
    t1Value = value;
}

void t2ValueChanged(int value){
    t2Value = value;
}

void appertureValueChanged(QVariant value){
    appertureValue = value.toInt();
    qDebug() << "Apperture: " << appertureValue;
}
void testSliderValChanged(int value){
    qDebug() << "Test: " << value;
}
void refreshLayout()
{
    wgtSub->adjustSize();
}

private:
int t1Value = 30;
int t2Value = 3;
int appertureValue = 3;

void initWidget()
{
    SliderLayout* t1SliderLayout = new SliderLayout("threshold1\n[0-100]", t1Value);
    connect(t1SliderLayout, SIGNAL(sliderValueChanged(int)),
            this, SLOT(t1ValueChanged(int)));

    SliderLayout* t2SliderLayout = new SliderLayout("threshold2\n[0-100]", t2Value);
    connect(t2SliderLayout, SIGNAL(sliderValueChanged(int)),
            this, SLOT(t2ValueChanged(int)));

    QList<QVariant> appertureMap;
    appertureMap.append({3, 5, 7});
    LabelledComboBox* selectAppertureCB =
            new LabelledComboBox("Apperture Value",
                                 appertureMap, 50);

    connect(selectAppertureCB,SIGNAL(currentIndexChanged(QVariant)),
            this,SLOT(appertureValueChanged(QVariant)));


    vBoxSub->addLayout(t1SliderLayout);
    vBoxSub->addLayout(t2SliderLayout);
    vBoxSub->addLayout(selectAppertureCB);

    // FIXME: Range Box hiding causes Hybrid Slider to retain height
    //        HybridSlider* hybridGG = new HybridSlider(this, "threshold1", t1Value, 0, 100);
    //        connect(hybridGG, SIGNAL(sliderValueChanged(int)),
    //                this, SLOT(t1ValueChanged(int)));
    //        connect(hybridGG, SIGNAL(editApplyClicked()),
    //                this, SLOT(refreshLayout()));

    //        vBoxSub->addWidget(hybridGG);

    BaseConfigWidget::initWidget();
}
};
