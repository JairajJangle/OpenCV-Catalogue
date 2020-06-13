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

#include "Window/MainWindow/mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    qDebug() << QStyleFactory::keys();
    //    a.setStyle(QStyleFactory::create("Fusion"));
    //    qApp->setStyle(QStyleFactory::create("Fusion"));

    //    QPalette darkPalette;
    //        darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    //        darkPalette.setColor(QPalette::WindowText, Qt::white);
    //        darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    //        darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    //        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    //        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    //        darkPalette.setColor(QPalette::Text, Qt::white);
    //        darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    //        darkPalette.setColor(QPalette::ButtonText, Qt::white);
    //        darkPalette.setColor(QPalette::BrightText, Qt::red);
    //        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    //        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    //        darkPalette.setColor(QPalette::HighlightedText, Qt::white);

    //        qApp->setPalette(darkPalette);

    //        qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

    MainWindow w;
    w.show();
    return a.exec();
}
