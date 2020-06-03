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
#include <QMutex>

// OpenCV libs

#include "CustomWidgets/ClickableLabel/clickablelabel.h"

class BaseConfigWidget : public QWidget
{
    Q_OBJECT
private:
    QScrollArea *scrl = new QScrollArea();
    QWidget *wgtSub = new QWidget();

protected:
    // TODO: Check need of mutex, probably not required -> remove
    QMutex m;

    QWidget *wgtMain = new QWidget();
    QWidget* configWidget;

    /*
     * Assing Values to operationName and moreInfoLink in Constructor of
     * Derived class of OpenCV operation widgets
     */
    QString operationName = "No operation Selected";
    QString moreInfoLink = "";

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
    }
    ~BaseConfigWidget(){}

    /*
     * Returned widget to be used by calling widget/application(Main Window)
     * to set it in Scroll Area
     */
    QWidget* getConfigWidget()
    {
        return configWidget;
    }

    /*
     * Returns name of operation to be used by calling widget/application(Main Window)
     * to update Operation Name label
     */
    QString getOperationName()
    {
        return operationName;
    }

    /*
     * Returns URL of opertaion documentation in OpenCV docs to be used by calling
     * widget/application(Main Window) to update Operation Name label
     */
    QString getInfoURL()
    {
        return moreInfoLink;
    }

    /*
     * Shows exploded windows of OpenCV operation to give user more insights
     * Perform displaying/hiding of exploded views and returns status of operation
     */
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

    /*
     * Get state of exploded view
     */
    bool isExplodedViewEnabled()
    {
        return  explodedViewEnabled;
    }

    /*
     * Override this function in individual operation classes
     */
    virtual cv::Mat getProcessedImage(cv::Mat inputImage){
        m.lock(); // Lock mutex at function start

        // Do Operations

        m.unlock(); // Unlock mutex before return
        return inputImage;
    }

    /*
     * Super call this function at the end of overriden initWidget() function in
     * each Operation class to actually show configuration widget in the Scroll Area
     */
    virtual void initWidget()
    {
        vboxMain->addWidget(wgtSub);
        scrl->setWidget(wgtMain);
        configWidget = scrl;
    }
};

#endif // BASECONFIGWIDGET_H
