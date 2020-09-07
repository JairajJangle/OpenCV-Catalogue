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

#include "CustomWidgets/baseconfigwidget.h"
#include "Utils/constants.h"

void BaseConfigWidget::beginPointChanged(QPoint point)
{
    if(chainMenuWidget->getRadioButton()->isChecked())
        begin = cv::Point(point.x(), point.y());
}

BaseConfigWidget::BaseConfigWidget(){
    begin =cv::Point(-1, -1);
    end =cv::Point(-1, -1);

    connect(chainMenuWidget, &ChainMenuWidget::radioButtonChecked,
            this, [=]() {
        emit operationSelected(paramAdjustWidget);
    });

    changeWidgetsStyleSheet(isDarkModeOn);
}

QWidget* BaseConfigWidget::getConfigWidget()
{
    return wgtSub;
}

ChainMenuWidget* BaseConfigWidget::getChainMenuWidget()
{
    chainMenuWidget->setCurrentOperation(operationName);
    return chainMenuWidget;
}

ParamAdjustWidget* BaseConfigWidget::getParamAdjustWidget()
{
    return paramAdjustWidget;
}

QMap<QString, cv::Mat> BaseConfigWidget::getExplodedViewMats()
{
    return explodedView;
}

void BaseConfigWidget::changeWidgetsStyleSheet(bool isDarkMode)
{
    paramAdjustWidget->setInfoIconStyleSheet(isDarkMode);
    chainMenuWidget->setStyleSheet(isDarkMode);
}

QString BaseConfigWidget::getOperationName()
{
    return operationName;
}

QString BaseConfigWidget::getInfoURL()
{
    return moreInfoLink;
}

bool BaseConfigWidget::setExplodedView([[maybe_unused]] bool explodedViewEnabled)
{
    /*
     * If exploded == true:
     *              Should return true if exploded view is possible else false
     * If exploded == false:
     *              Ignore return value
     */
    return this->explodedViewEnabled;
}

bool BaseConfigWidget::isExplodedViewEnabled()
{
    return  explodedViewEnabled;
}

QUuid BaseConfigWidget::getUUID()
{
    return uuid;
}

cv::Mat BaseConfigWidget::getProcessedImage(cv::Mat inputImage)try
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

void BaseConfigWidget::initWidget()
{
    // vBoxSub->setAlignment(Qt::AlignHCenter);
    wgtSub->setMinimumWidth(370);
    wgtSub->setMaximumWidth(420);

    paramAdjustWidget->setContentLayout(wgtSub,
                                        &operationName,
                                        &moreInfoLink);
}
