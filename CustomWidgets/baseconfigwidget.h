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

#include <opencv2/opencv.hpp>

// QT libs
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

#include "Utils/constants.h"

#include "CustomWidgets/ClickableLabel/clickablelabel.h"
#include "CustomWidgets/ChainMenuWidget/chainmenuwidget.h"
#include "CustomWidgets/ParamAdjustWidget/paramadjustwidget.h"

class BaseConfigWidget : public QWidget
{
    Q_OBJECT

protected:
    /**
     * @brief wgtSub Sub-widget of BaseConfigWidget
     *  This widget is parent to the QVBoxLayout where all the
     *  configuration widgets and layouts are added in respective
     *  derived classes (OpenCV Operation widget classes)
     */
    QWidget *wgtSub = new QWidget();

    /**
     * @brief vBoxSub is the main QVBoxLayout which should be populated in
     *  derived classes @fn initWidget with all the adjustment widgets
     *
     *  Parent of vBoxSub is @var wgtSub
     */
    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

    /**
     * @brief chainMenuWidget Chain Menu Widget is member of this class
     */
    ChainMenuWidget* chainMenuWidget = new ChainMenuWidget();

    /**
     * @brief paramAdjustWidget This widget contains all the parameter adjustment widget
     *  Content for this widget is @var wgtSub, @var moreInfoLink, @var operationName
     */
    ParamAdjustWidget* paramAdjustWidget = new ParamAdjustWidget();

    /**
     * @brief operationName Holds the name of the selected operation
     *  This is set in constructor of each derived class
     */
    QString operationName = Strings::noOperationSelected;

    /**
     * @brief moreInfoLink Holds the documentation link for the selected operation
     *  This is set in constructor of each derived class
     */
    QString moreInfoLink = "";

    bool explodedViewEnabled = false;

signals:
    void removeOperationSignal();
    void operationSelected(ParamAdjustWidget*);

public:
    cv::Point begin;
    cv::Point end;

    /**
     * 1. Set @param begin and @param end to -1, -1 which are considered to be the
     * default selection when there has been no mouse click on outputLabel in
     * @class MainWindow
     *
     * 2. Connect Radio button select signal from @class ChainMenuWidget
     * signal operationSelected(ParamAdjustWidget*) is connected in @class MainWindow
     * to display the obtained parameter adjust widget in the parameter adjust box
     * in MainWindow UI
     */
    BaseConfigWidget(){
        begin =cv::Point(-1, -1);
        end =cv::Point(-1, -1);

        connect(chainMenuWidget, &ChainMenuWidget::radioButtonChecked,
                this, [=]() {
            emit operationSelected(paramAdjustWidget);
        });

        changeWidgetsStyleSheet(isDarkModeOn);
    }
    virtual ~BaseConfigWidget(){}

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

    ParamAdjustWidget* getParamAdjustWidget()
    {
        return paramAdjustWidget;
    }

    void changeWidgetsStyleSheet(bool isDarkMode)
    {
        paramAdjustWidget->setInfoIconStyleSheet(isDarkMode);
        chainMenuWidget->setStyleSheet(isDarkMode);
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
    /**
     * @brief getInfoURL Returns URL of opertaion documentation in OpenCV docs
     * @return Documentation URL of selected OpenCV Operation
     */
    QString getInfoURL()
    {
        return moreInfoLink;
    }

    /**
     * @brief setExplodedView Shows exploded windows of OpenCV operation to give user more insights
     * @param explodedViewEnabled
     * @return Status of operation, true if Exploded view is enabled else false
     */
    virtual bool setExplodedView([[maybe_unused]] bool explodedViewEnabled)
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
        // Do Operations

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
    wgtSub->setMinimumWidth(370);
    wgtSub->setMaximumWidth(420);

    paramAdjustWidget->setContentLayout(wgtSub,
                                        operationName,
                                        moreInfoLink);
}
};
