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

/*
 *  Source of this custom logger: https://doc.qt.io/qt-5/qtglobal.html#qInstallMessageHandler
 */

#pragma once

#include <QtGlobal>
#include <QString>
#include <QDateTime>

#include <stdio.h>
#include <stdlib.h>

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray dateTime = QDateTime::currentDateTime().toString(Qt::DateFormat::ISODateWithMs).toLocal8Bit();
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "\u001b[37m%s : \x1b[32mDebug:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n",
                dateTime.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "\u001b[37m%s : \x1b[34mInfo:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n",
                dateTime.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "\u001b[37m%s : \x1b[33mWarning:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n",
                dateTime.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "\u001b[37m%s : \x1b[31mCritical:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n",
                dateTime.constData(), localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "\u001b[37m%s : \x1b[31mFatal:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n",
                dateTime.constData(), localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}
