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

#include <QFrame>
#include <QGridLayout>
#include <QToolButton>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

#include "Utils/constants.h"

#include "CustomWidgets/dividerline.h"

class ParamAdjustWidget : public QFrame {
    Q_OBJECT

public:
    explicit ParamAdjustWidget(QWidget *parent = 0);

    /**
     * @brief setContentLayout Adds Content to parameter adjust widget. This is invoked
     *  from OpenCV operation widgets to set BaseConfigWidget::wgtSub as content widget
     * @param contentWidget takes QWidget as input to set the content widget for ParamAdjustWidget
     * @param title Name of the OpenCV operation
     * @param infoLink Documentation link of OpenCV operation
     */
    void setContentLayout(QWidget* contentWidget,
                          const QString title,
                          const QString infoLink);

    /**
     * @brief setInfoIconStyleSheet tO change style sheet of the info button
     * @param isDarkMode Set true for Dark Theme, false for Light Theme
     */
    void setInfoIconStyleSheet(bool isDarkMode);

signals:
    /**
     * @brief infoButtonClicled Signal is emitted when click event on info button is
     *  recorded
     */
    void infoButtonClicled();

private:
    QGridLayout* mainLayout = new QGridLayout();

    DividerLine* dividerLine = new DividerLine(1);

    /**
     * @brief titleLabel Label to display OpenCV operation name
     */
    QLabel* titleLabel = new QLabel();

    /**
     * @brief infoButton Button to open OpenCV opertaion info link
     */
    QToolButton* infoButton = new QToolButton();
    int row = 0;

    /**
     * @brief infoButtonLightStyleSheet Light Theme stylesheet for info button
     */
    const QString infoButtonLightStyleSheet = QString("QToolButton#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}"
                                           "QToolButton:pressed#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info_sel.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}");

    /**
     * @brief infoButtonDarkStyleSheet Dark Theme stylesheet for info button
     */
    const QString infoButtonDarkStyleSheet = QString("QToolButton#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info_light.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}"
                                           "QToolButton:pressed#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info_light_sel.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}");
};
