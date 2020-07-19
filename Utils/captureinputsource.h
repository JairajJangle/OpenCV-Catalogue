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
    enum InputSourceType {HARDWARE_CAM, FILE, NETWORK_STREAM};

    explicit CaptureInputSource(QObject* parent = nullptr)
        :QObject(parent)
    {
        inputSourceCaptureTImer = new QTimer(this);
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
            cap.release();
        },
        Qt::QueuedConnection);

        connect(this, &CaptureInputSource::setInputSource,
                this,
                [=](QString inputSource, int inputSourceType){
            emit stopCapture();
            this->inputSourceType = InputSourceType(inputSourceType);
            this->inputSource = inputSource;
            emit startTimer(1000);
        },
        Qt::QueuedConnection);

        connect(inputSourceCaptureTImer, SIGNAL(timeout()),
                this, SLOT(captureSource()));
    }
    ~CaptureInputSource()
    {
        cap.release();
        qDebug() << "VideoCapture release() called";
    }

signals:
    void sourceCaptured(cv::Mat originalImg);
    void sourceCaptureError(QString);
    void setInputSource(QString inputSource, int inputSourceType);
    void startTimer(int);
    void stopCapture();

private slots:
    void captureSource()
    {
        try{
            bool isSuccess = true;
            if(!cap.isOpened())
            {
                openSource();

                // img =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
                // resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
            }

            try {
                double fps = cap.get(cv::CAP_PROP_FPS);

                inputSourceCaptureTImer->setInterval(
                            inputSourceType == NETWORK_STREAM ? 10 : (1000/fps));

                if(inputSourceType == FILE)
                {
                    /*
                     * TODO: Implement a more elegant way to differentiate between Image and Video
                     *
                     * First try to read input source as Video File
                     * If it is not a continuos stream then it is a Image File
                     */
                    isSuccess = cap.read(img);

                    /*
                     * If the selected path is not a video then try to read it as an Image
                     */
                    if(!isSuccess)
                    {
                        img = cv::imread(inputSource.toStdString());
                        isSuccess = !img.empty();
                    }
                }
                else if(inputSourceType == NETWORK_STREAM || inputSourceType == HARDWARE_CAM)
                    isSuccess = cap.read(img);

                // Avoid empty image resizing error
                if(!cv::Size(img.rows , img.rows).empty())
                    resize(img, resizedImg, cv::Size(640, 480));

                if(!isSuccess)
                {
                    emit sourceCaptureError("Cannot read the input source");
                    emit stopCapture();
                    return;
                }

                emit sourceCaptured(img);

            } catch (cv::Exception& e) {
                emit sourceCaptureError(e.what());
            }
        }
        catch (cv::Exception& e) {
            emit sourceCaptureError(e.what());
        }
    }

private:
    QThread *camThread = new QThread;
    QTimer *inputSourceCaptureTImer;

    QString inputSource = "";
    cv::VideoCapture cap;

    InputSourceType inputSourceType = FILE;

    //Mat to store image from camera
    cv::Mat img, resizedImg;

    void openSource()
    {
        cap.release();

        if (QRegExp(RegExps::onlyDigits).exactMatch(inputSource))
            cap.open(inputSource.toInt()); // Camera Index
        else
            cap.open(inputSource.toStdString()); // Source File path
    }

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
