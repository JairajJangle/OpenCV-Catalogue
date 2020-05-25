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

#ifndef BASECONFIGWIDGET_H
#define BASECONFIGWIDGET_H

#include <iostream>

#include <opencv2/opencv.hpp>

// QT libs
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

// OpenCV libs

#include "CustomWidgets/ClickableLabel/clickablelabel.h"

class BaseConfigWidget
{
private:
    QScrollArea *scrl = new QScrollArea();
    QWidget *wgtSub = new QWidget();

protected:
    QWidget *wgtMain = new QWidget();

    QWidget* configWidget;
    QString operationName = "No operation Selected";
    QString moreInfoLink = "";
    ClickableLabel* labelInfo = new ClickableLabel();

    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

    bool explodedViewEnabled = false;

private:
    QVBoxLayout *vboxMain = new QVBoxLayout(wgtMain);

public:
    cv::Point begin;
    cv::Point end;

    BaseConfigWidget(){
        begin =cv::Point(-1, -1);
        end =cv::Point(-1, -1);
        labelInfo->setText("More Info >>");
    }
    ~BaseConfigWidget(){}

    QWidget* getConfigWidget()
    {
        return configWidget;
    }

    QString getOperationName()
    {
        return operationName;
    }

    QString getInfoURL()
    {
        return moreInfoLink;
    }

    // Funtion to show extra windows either in QT UI or OpenCV NamedWindow
    virtual bool setExplodedView(bool explodedViewEnabled)
    {
        /*
         * If exploded == true:
         *              Should return true if exploded view is possible else false
         * If exploded == false:
         *              Ignore return value
         */
        return this->explodedViewEnabled;
    }

    bool isExplodedViewEnabled()
    {
        return  explodedViewEnabled;
    }

    virtual cv::Mat getProcessedImage(cv::Mat inputImage){
        return inputImage;
    }

    virtual void initWidget()
    {
        vboxMain->addWidget(wgtSub);
        scrl->setWidget(wgtMain);
        configWidget = scrl;
    }
};

#endif // BASECONFIGWIDGET_H
