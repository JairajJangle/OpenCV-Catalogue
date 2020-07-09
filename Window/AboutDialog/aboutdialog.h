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

// QT Libs
#include <QDialog>
#include <QDesktopServices>
#include <QGraphicsDropShadowEffect>
#include <QUrl>

#include "Utils/constants.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();


private slots:
    void openURL(const QString& url);

private:
    const QString githubSourceLink = "https://github.com/JairajJangle/Open-CV-Catalogue";
    const QString githubIssuesLink = "https://github.com/JairajJangle/Open-CV-Catalogue/issues";

    const QString paypalDonateUrl = "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=PPXTF24LWH86U";
    const QString liberaPayUrl = "https://liberapay.com/FutureJJ/donate";

    Ui::AboutDialog *ui;
};
