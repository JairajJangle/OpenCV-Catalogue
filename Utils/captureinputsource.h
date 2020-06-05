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

#ifndef CAPTUREINPUTSOURCE_H
#define CAPTUREINPUTSOURCE_H

// QT libs
#include <QThread>
#include <QTimer>
#include <QIODevice>
#include <QFile>
#include <QtDebug>

// OpenCV libs
#include <opencv2/opencv.hpp>

// CaptureInputSource extends QThread
class CaptureInputSource : public QThread
{
    Q_OBJECT
public:
    //Mat to store image from camera
    cv::Mat img, resizedImg;

    std::string inputSource = "";

    /*
     * Constructor to start single shot timer and connect the signal once every loop
     * in StartCam() slot
     */
    CaptureInputSource(std::string inputSource)
    {
        this->inputSource = inputSource;
        start_cam_once_timer->setInterval(100);
        start_cam_once_timer->setSingleShot(true);
        connect(start_cam_once_timer, SIGNAL(timeout()), this, SLOT(StartCam()));
        start_cam_once_timer->start();
    }

signals:
    //Signal to be emitted from StartCam Slot which is caught by mainwindow
    void SourceCaptured();
    void SourceCaptureError(QString);

public slots:
    void StartCam()
    {
        try{
            openSource();

            img =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);        resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);

            //TODO: apply FPS
            while(1)
            {
                try {
                    double fps = cap.get(cv::CAP_PROP_FPS);
                    bool isSuccess = cap.read(img);

                    if(!cv::Size(img.rows , img.rows).empty()) // Avoid empty image resizing error
                        resize(img, resizedImg, cv::Size(640, 480));

                    if(!isSuccess)
                    {
                        emit SourceCaptureError("Cannot read the frame from the source");
                        //                        cap.open("/home/jairaj/Desktop/Projects/JAS.mp4");
                        openSource();
                        continue; // retry
                    }
                    //            img = loadFromQrc(":/test_file/cam_test_2.jpg");
                    //img =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //Black for Simulation Purpose
                    emit SourceCaptured();
                    QThread::usleep(1000000/fps);
                } catch (cv::Exception& e) {
                    emit SourceCaptureError(e.what());
                }
            }
        }
        catch (cv::Exception& e) {
            emit SourceCaptureError(e.what());
        }
    }

public:
    ~CaptureInputSource()
    {
        cap.release();
        printf("Camera Closed\n");
    }

    void relesaseCap()
    {
        cap.release();
    }

    void openSource()
    {
        qDebug() << "Path: "
                 << QString::fromStdString(inputSource);
        cap.release();
        if(std::all_of(inputSource.begin(), inputSource.end(), ::isdigit)) // check if only contains digits
        {
            cap.open(stoi(inputSource)); // For Camera number
        }
        else
            cap.open(inputSource); // For file path
    }

private:

    cv::VideoCapture cap;
    QTimer *start_cam_once_timer = new QTimer(this);

    //Function to convert QT res image file to OpenCVcv::Mat object
    cv::Mat loadFromQrc(QString qrc, int flag = cv::IMREAD_COLOR)
    {
        //double tic = double(getTickCount());

        QFile file(qrc);
        cv::Mat m;
        if(file.open(QIODevice::ReadOnly))
        {
            qint64 sz = file.size();
            std::vector<uchar> buf(sz);
            file.read((char*)buf.data(), sz);
            m = cv::imdecode(buf, flag);
        }

        //double toc = (double(getTickCount()) - tic) * 1000.0 / getTickFrequency();
        //qDebug() << "OpenCV loading time: " << toc;

        return m;
    }
};

#endif // CAPTUREINPUTSOURCE_H
