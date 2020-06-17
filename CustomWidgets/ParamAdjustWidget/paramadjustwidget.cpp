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

#include <QPropertyAnimation>

#include "paramadjustwidget.h"
#include <QDebug>

ParamAdjustWidget::ParamAdjustWidget(QWidget *parent) : QFrame(parent)
{
    toggleButton->setText(Strings::noOperationSelected);
    toggleButton->setStyleSheet("QToolButton { border: none; }");
    toggleButton->setMinimumHeight(50);

    infoButton->setFixedSize(25, 25);
    infoButton->setObjectName("infoButton");
    infoButton->setStyleSheet(infoButtonStyleSheet);
    infoButton->hide();

    headerLine2->setFrameShape(QFrame::HLine);
    headerLine2->setFrameShadow(QFrame::Sunken);
    headerLine2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    QHBoxLayout* titleHBox = new QHBoxLayout();
    titleHBox->addWidget(toggleButton);
    titleHBox->addStretch();
    titleHBox->addWidget(infoButton);

    mainLayout->setVerticalSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(titleHBox, row, 0, 1, 8);
    mainLayout->addWidget(headerLine2, ++row, 0, 1, 8);
    setLayout(mainLayout);

    this->setFrameShape(QFrame::Box);
    this->setStyleSheet("QFrame { border: none; }");
    this->setLineWidth(1);
}

void ParamAdjustWidget::setContentLayout(QWidget* contentLayout,
                                         const QString title,
                                         const QString infoLink)
{
    toggleButton->setText(title);

    mainLayout->addWidget(contentLayout, 3, 0, 1, 8, Qt::AlignTop);
    setLayout(mainLayout);

    if(infoLink != "")
    {
        infoButton->show();
        connect(infoButton, &QToolButton::released,
                this, [=]() {
            QDesktopServices::openUrl(QUrl(infoLink));
        });
    }
}
