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

// QT libs
#include <QThread>
#include <QTimer>
#include <QIODevice>
#include <QObject>
#include <QFile>
#include <QtDebug>

// OpenCV libs
#include <opencv2/opencv.hpp>

// Utils
#include <Utils/constants.h>

class CaptureInputSource : public QObject
{
    Q_OBJECT
public:
    QThread *camThread = new QThread;

    //Mat to store image from camera
    cv::Mat img, resizedImg;

    QString inputSource = "";

    /*
     * Constructor: Start Single Shot Timer and connect timeout signal to start
     * Video Capture read loop
     */
    explicit CaptureInputSource(QObject* parent = nullptr)
        :QObject(parent)
    {
        inputSourceCaptureTImer = new QTimer(nullptr);
        this->moveToThread(camThread);
        inputSourceCaptureTImer->moveToThread(camThread);
        QObject::connect(camThread, &QThread::finished,
                         this, &QObject::deleteLater);
        camThread->start();

        connect(this, &CaptureInputSource::startTimer,
                this,
                [=](int initialDelay){
            inputSourceCaptureTImer->start(initialDelay);
            inputSourceCaptureTImer->setInterval(1000);
        },
        Qt::QueuedConnection);

        connect(this, &CaptureInputSource::stopCapture,
                this,
                [=](){
            inputSourceCaptureTImer->stop();
            releaseCap();
        },
        Qt::QueuedConnection);

        connect(this, &CaptureInputSource::setInputSource,
                this,
                [=](QString inputSource){
            retryCount = 0;
            emit stopCapture();
            this->inputSource = inputSource;
            emit startTimer(1000);
        },
        Qt::QueuedConnection);

        connect(inputSourceCaptureTImer, SIGNAL(timeout()),
                this, SLOT(StartCam()));
    }

signals:
    //Signal to be emitted from StartCam Slot which is caught by mainwindow
    void SourceCaptured();
    void SourceCaptureError(QString);
    void setInputSource(QString inputSource);
    void startTimer(int);
    void stopCapture();

public slots:
    void StartCam()
    {
        try{
            if(!cap.isOpened())
            {
                openSource();
                ++retryCount;

                if(retryCount >= retryLimit)
                {
                    emit stopCapture();
                    return;
                }

                qDebug() << "Camera Opened";

                img =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
                resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
            }

            try {
                double fps = cap.get(cv::CAP_PROP_FPS);

                qDebug () << "Intervals: " << fps;

                inputSourceCaptureTImer->setInterval(
                            instantRefresh ? 10 : (1000/fps));

                bool isSuccess = cap.read(img);

                // Avoid empty image resizing error
                if(!cv::Size(img.rows , img.rows).empty())
                    resize(img, resizedImg, cv::Size(640, 480));

                if(!isSuccess)
                {
                    emit SourceCaptureError("Cannot read the input source");
                    emit stopCapture();
                    return;
                }

                emit SourceCaptured();

            } catch (cv::Exception& e) {
                emit SourceCaptureError(e.what());
            }
        }
        catch (cv::Exception& e) {
            emit SourceCaptureError(e.what());
        }
    }

public:
    ~CaptureInputSource()
    {
        releaseCap();
        qDebug() << "Camera Closed";
    }

    void releaseCap()
    {
        cap.release();
    }

    void openSource()
    {
        qDebug() << "Path: " << inputSource;
        releaseCap();

        if (QRegExp(RegExps::onlyDigits).exactMatch(inputSource))
            cap.open(inputSource.toInt()); // For Camera number
        else
            cap.open(inputSource.toStdString()); // For file path
    }

    void setInstantFrameRefresh(bool instantRefresh)
    {
        this->instantRefresh = instantRefresh;
    }

private:
    cv::VideoCapture cap;
    QTimer *inputSourceCaptureTImer;

    short retryCount = 0;
    const short retryLimit = 3;

    // Set true for IP/Normal camera input source
    bool instantRefresh = false;

    //Function to convert QT res image file to OpenCVcv::Mat object
    cv::Mat loadFromQrc(QString qrc, int flag = cv::IMREAD_COLOR)
    {
        QFile file(qrc);
        cv::Mat m;
        if(file.open(QIODevice::ReadOnly))
        {
            qint64 sz = file.size();
            std::vector<uchar> buf(sz);
            file.read((char*)buf.data(), sz);
            m = cv::imdecode(buf, flag);
        }

        return m;
    }
};
