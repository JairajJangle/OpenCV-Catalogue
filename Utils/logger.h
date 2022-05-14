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

#include <Utils/utils.h>

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray dateTime = QDateTime::currentDateTime().toString(Qt::DateFormat::ISODateWithMs).toLocal8Bit();
    QByteArray localMsg = msg.toLocal8Bit();

    // FIXME: Logging level is not relevant. Consider Loggin Level for Logs

    std::string tagFile = "\n%s : Unknown: %s (%s:%u, %s)";
    std::string tagStd = "\u001b[37m%s :\x1b[32m Unknown:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n";

    switch (type) {
    case QtDebugMsg:
        tagFile = "\n%s : Debug: %s (%s:%u, %s)";
        tagStd = "\u001b[37m%s :\x1b[32m Debug:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n";
        break;
    case QtInfoMsg:
        tagFile = "\n%s : Info: %s (%s:%u, %s)";
        tagStd = "\u001b[37m%s :\x1b[34m Info:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n";
        break;
    case QtWarningMsg:
        tagFile = "\n%s : Warning: %s (%s:%u, %s)";
        tagStd = "\u001b[37m%s :\x1b[33m Warning:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n";
        break;
    case QtCriticalMsg:
        tagFile = "\n%s : Critical: %s (%s:%u, %s)";
        tagStd = "\u001b[37m%s :\x1b[31m Critical:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n";
        break;
    case QtFatalMsg:
        tagFile = "\n%s : Fatal: %s (%s:%u, %s)";
        tagStd = "\u001b[37m%s :\x1b[31m Fatal:\x1b[0m %s \x1b[36m(%s:%u, %s)\x1b[0m\n";
    }

    if(fp != NULL)
    {
        fprintf(fp,
                tagFile.c_str(),
                dateTime.constData(),
                localMsg.constData(),
                context.file, context.line, context.function);
        fflush(fp);
    }
    else if(fp == NULL)
    {
        fprintf(stderr, "\x1b[33m Warning:\x1b[0m %s ", "Error writing to log file");
    }

#ifdef QT_DEBUG
    fprintf(stderr,
            tagStd.c_str(),
            dateTime.constData(),
            localMsg.constData(),
            context.file, context.line, context.function);
#endif

    if(type == QtFatalMsg)
        abort();
}
