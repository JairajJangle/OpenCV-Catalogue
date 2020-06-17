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

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

#include "Utils/constants.h"

class ParamAdjustWidget : public QFrame {
    Q_OBJECT

public:
    explicit ParamAdjustWidget(QWidget *parent = 0);
    void setContentLayout(QWidget* contentLayout,
                          const QString title,
                          const QString infoLink);
    void setInfoButtonVisibility(bool visible);

signals:
    void infoButtonClicled();

private:
    QGridLayout* mainLayout = new QGridLayout();
    QLabel* toggleButton = new QLabel();
    QFrame* headerLine = new QFrame();
    QFrame* headerLine2 = new QFrame();
    QToolButton* infoButton = new QToolButton();
    int row = 0;

    QString infoButtonStyleSheet = QString("QToolButton#infoButton"
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
};
