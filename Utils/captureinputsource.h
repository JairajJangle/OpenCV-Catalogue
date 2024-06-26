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
#include <QRegularExpression>

// OpenCV libs
#include <opencv2/opencv.hpp>

// Utils
#include <Utils/constants.h>

class CaptureInputSource : public QObject
{
    Q_OBJECT
public:
    enum InputSourceType {HARDWARE_CAM, FILE, NETWORK_STREAM};

signals:
    /**
     * @brief sourceCaptured Signal is emiitted when a frame is captured from
     *  the input source
     * @param originalImg Full resolution image captured from the input source
     */
    void sourceCaptured(cv::Mat originalImg);

    /**
     * @brief sourceCaptureError is emitted when there is an error in capturing
     *  frame from source
     */
    void sourceCaptureError(QString);

    /**
     * @brief setInputSource should be triggered the calling class to
     *  set/change the input source
     * @param inputSourcePath Path of Input source
     * @param inputSourceType Type of source, refer to
     *  @enum CaptureInputSource::InputSourceType
     */
    void setInputSource(int inputSourceType, QString inputSourcePath);

    /**
     * @brief stopCapture To be emitted to stop the ongoing input source capture
     */
    void stopCapture();

    /**
     * @brief updateFPS emitted on input source FPS change
     * @param fps is equal to the value as received from OpenCV CAP_PROP_FPS
     */
    void updateFPS(int fps);

private: signals:
    /**
     * @brief startCaptureTimer Internal signal to start source frame capture on a
     *  timely basis
     * @param delay The initial delay to start capture
     */
    void startCaptureTimer(int delay);

private slots:
    void captureSource()
    {
        try
        {
            if(!cap.isOpened())
            {
                openSource();
            }
        }
        catch (cv::Exception& e)
        {
            emit sourceCaptureError(e.what());
            emit stopCapture();
            return;
        }

        try
        {
            bool isSuccess = true;
            auto prevFPS = fps;

            // FIXME: FPS for Network Streams turns out to be incorrect
            fps = cap.get(cv::CAP_PROP_FPS);

            if(prevFPS != fps)
                emit updateFPS(fps);

            inputSourceCaptureTimer->setInterval(
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
                    img = cv::imread(inputSourcePath.toStdString());
                    isSuccess = !img.empty();
                }
            }
            else if(inputSourceType == NETWORK_STREAM || inputSourceType == HARDWARE_CAM)
                isSuccess = cap.read(img);

            if(!isSuccess)
            {
                if(inputSourceType == FILE)
                {
                    qDebug() << "Retrying to open FILE type source";
                    openSource();
                    return;
                }
                emit sourceCaptureError("Cannot read the input source");
                emit stopCapture();
                return;
            }

            emit sourceCaptured(img);

        } catch (cv::Exception& e)
        {
            emit sourceCaptureError(e.what());
            emit stopCapture();
            return;
        }

    }

public:
    // Mat to store image from camera
    inline static cv::Mat img;

    explicit CaptureInputSource(QObject* parent = nullptr)
        :QObject(parent)
    {
        // Input Source Capture is done on a separate thread
        inputSourceCaptureTimer = new QTimer(this);
        this->moveToThread(camThread);
        inputSourceCaptureTimer->moveToThread(camThread);
        QObject::connect(camThread, &QThread::finished,
                         this, &QObject::deleteLater);
        camThread->start();

        connect(this, &CaptureInputSource::startCaptureTimer,
                this,
                [=](int initialDelay){
            inputSourceCaptureTimer->start(initialDelay);
            inputSourceCaptureTimer->setInterval(initialDelay);
        },
        Qt::QueuedConnection);

        connect(this, &CaptureInputSource::stopCapture,
                this,
                [=](){
            // Reset input source FPS to 0
            emit updateFPS(0);

            // Stop source capture timer
            inputSourceCaptureTimer->stop();

            // Release source device be it a file or a stream
            cap.release();
        },
        Qt::QueuedConnection);

        connect(this, &CaptureInputSource::setInputSource,
                this,
                [=](int inputSourceType, QString inputSourcePath){
            emit stopCapture();

            // Reset retry count
            retryCount = 0;

            this->inputSourceType = InputSourceType(inputSourceType);
            this->inputSourcePath = inputSourcePath;
            emit startCaptureTimer(initialDelay);
        },
        Qt::QueuedConnection);

        connect(inputSourceCaptureTimer, SIGNAL(timeout()),
                this, SLOT(captureSource()));
    }

    int getCurrentFPS()
    {
        return fps;
    }

    ~CaptureInputSource()
    {
        cap.release();
        qDebug() << "VideoCapture release() called";
    }

private:
    QThread *camThread = new QThread;
    QTimer *inputSourceCaptureTimer;

    QString inputSourcePath = "";
    cv::VideoCapture cap;

    InputSourceType inputSourceType = FILE;

    double fps = -1;

    const int initialDelay = 1000; // ms

    int retryCount = 0;
    int retryLimit = 3;

    void openSource()
    {
        retryCount++;
        bool isStringNumber; // True if source path is valid number string
        int convertedInt = inputSourcePath.toInt(&isStringNumber, 10);

        cap.release();

        if (isStringNumber)
            cap.open(convertedInt); // Camera Index
        else
            cap.open(inputSourcePath.toStdString()); // Source File path
    }
};
