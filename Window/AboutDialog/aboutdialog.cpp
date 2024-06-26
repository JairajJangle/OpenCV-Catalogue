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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    this->setFixedSize(525, 615);

    ui->labelAppName->setText(Info::appName);
    ui->labelVersion->setText(Info::version);

    ui->labelJairajJangle->setTextInteractionFlags(Qt::TextBrowserInteraction);

    ui->verticalLayout->setAlignment(Qt::AlignHCenter);

    connect(ui->labelJairajJangle,SIGNAL(linkActivated(const QString&)),this,SLOT(openURL(const QString&)));
    connect(ui->labelCopyright,SIGNAL(linkActivated(const QString&)),this,SLOT(openURL(const QString&)));

    connect(ui->labelQDSSName,SIGNAL(linkActivated(const QString&)),this,SLOT(openURL(const QString&)));
    connect(ui->labelQDSSLicense,SIGNAL(linkActivated(const QString&)),this,SLOT(openURL(const QString&)));

    connect(ui->buttonContribute, &QPushButton::released, this,
            [=]() {
        openURL(githubSourceLink);
    });
    connect(ui->buttonReportIssue, &QPushButton::released, this,
            [=]() {
        openURL(githubIssuesLink);
    });

    connect(ui->buttonDonatePaypal, &QPushButton::released, this,
            [=]() {
        openURL(paypalDonateUrl);
    });
    connect(ui->buttonDonateLiberaPay, &QPushButton::released, this,
            [=]() {
        openURL(liberaPayUrl);
    });
    connect(ui->buttonDonateUPI, &QPushButton::released, this,
            [=]() {
        openURL(upiPayUrl);
    });
}

void AboutDialog::openURL(const QString& link)
{
    QDesktopServices::openUrl(QUrl(link));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
