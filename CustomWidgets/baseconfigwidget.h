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

    /**
     * @brief explodedViewList Holds List of Matrix and corresponsing Label to be
     * displayed in exploded view
     */
    QMap<QString, cv::Mat> explodedView;

signals:
    void removeOperationSignal();
    void operationSelected(ParamAdjustWidget*);

public slots:
    void beginPointChanged(QPoint point)
    {
        if(chainMenuWidget->getRadioButton()->isChecked())
        begin = cv::Point(point.x(), point.y());
    }

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

    /**
     * @brief getConfigWidget To get the Configuration Widget
     * @return Returned widget to be used by calling widget/application(Main Window)
     * to set it in Scroll Area
     */
    QWidget* getConfigWidget()
    {
        return wgtSub;
    }

    /**
     * @brief getChainMenuWidget TO get the OpenCV Operation Menu widget
     * @return The Chain Menu Widget which lets user to add, change, remove OpenCV operations
     */
    ChainMenuWidget* getChainMenuWidget()
    {
        chainMenuWidget->setCurrentOperation(operationName);
        return chainMenuWidget;
    }

    /**
     * @brief getParamAdjustWidget To get the Parameter Adjustment Widget
     * @return The Parameter Adjustment widget which lets user change the OpenCV operation
     *  parameters in real-time.
     */
    ParamAdjustWidget* getParamAdjustWidget()
    {
        return paramAdjustWidget;
    }

    QMap<QString, cv::Mat> getExplodedViewMats()
    {
        return explodedView;
    }

    /**
     * @brief changeWidgetsStyleSheet Changes the theme of children widgets
     * @param isDarkMode Set true to enable dark mode style sheet to children widgets
     */
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

    /**
     * @brief getProcessedImage All OpenCV operations is done in this function
     *  Override this function in individual derived operation classes
     * @param inputImage The input image for OpenCV operation
     * @return The output image after OpenCV operation is performed
     */
    virtual cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        /*
         * Perform OpenCV operations here in derived classes
         */

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

/**
 * @brief initWidget Super call this function at the end of overriden initWidget() function in
 * each derived Operation class to actually set configuration widget in @var wgtSub
 */
virtual void initWidget()
{
    // vBoxSub->setAlignment(Qt::AlignHCenter);
    wgtSub->setMinimumWidth(370);
    wgtSub->setMaximumWidth(420);

    paramAdjustWidget->setContentLayout(wgtSub,
                                        &operationName,
                                        &moreInfoLink);
}
};
