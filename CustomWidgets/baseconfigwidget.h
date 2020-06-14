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
#include <QDebug>

#include "Utils/constants.h"

#include "CustomWidgets/ClickableLabel/clickablelabel.h"
#include "CustomWidgets/ChainMenuWidget/chainmenuwidget.h"
#include "CustomWidgets/Collapsible/collapsible.h"

class BaseConfigWidget : public QWidget
{
    Q_OBJECT
public:
    QWidget *wgtSub = new QWidget();

protected:
    // TODO: Check need of mutex, probably not required -> remove
    QMutex m;

    ChainMenuWidget* chainMenuWidget = new ChainMenuWidget();
    Collapsible* collapsible = new Collapsible();

    /*
     * Assing Values to operationName and moreInfoLink in Constructor of
     * Derived class of OpenCV operation widgets
     */
    QString operationName = Strings::noOperationSelected;
    QString moreInfoLink = "";

    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

    bool explodedViewEnabled = false;

signals:
    void removeOperationSignal();
    void operationSelected(Collapsible*);

public:
    cv::Point begin;
    cv::Point end;

    BaseConfigWidget(){
        begin =cv::Point(-1, -1);
        end =cv::Point(-1, -1);

        connect(collapsible, &Collapsible::removeButtonClicked,
                this, [=]() {
            emit removeOperationSignal();
        });

        connect(chainMenuWidget, &ChainMenuWidget::radioButtonChecked,
                this, [=]() {
            emit operationSelected(collapsible);
        });
    }
    ~BaseConfigWidget(){}

    /*
     * Returned widget to be used by calling widget/application(Main Window)
     * to set it in Scroll Area
     */
    QWidget* getConfigWidget()
    {
        return wgtSub;
    }

    ChainMenuWidget* getChainMenuWidget()
    {
        chainMenuWidget->setCurrentOperation(operationName);
        return chainMenuWidget;
    }

    Collapsible* getParamAdjustWidget()
    {
        return collapsible;
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
    virtual cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        m.lock(); // Lock mutex at function start

        // Do Operations

        m.unlock(); // Unlock mutex before return
        return inputImage;
    }
    catch(cv::Exception& e){
        throw e;
    } catch(std::exception& e) {
        throw e;
    }
    catch(...){
    throw std::string("Unknown Exception in ")
    + std::string(typeid(this).name()); // Append class name
}

    /*
     * Super call this function at the end of overriden initWidget() function in
     * each Operation class to actually show configuration widget in the Scroll Area
     */
    virtual void initWidget()
    {
//        vBoxSub->setAlignment(Qt::AlignHCenter);
        wgtSub->setMinimumWidth(400);
        wgtSub->setMaximumWidth(420);

        collapsible->setContentLayout(wgtSub,
                                      operationName,
                                      moreInfoLink);
    }
};

#endif // BASECONFIGWIDGET_H
