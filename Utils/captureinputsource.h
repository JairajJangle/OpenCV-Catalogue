/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

#ifndef CAPTUREINPUTSOURCE_H
#define CAPTUREINPUTSOURCE_H

// QT libs
#include <QThread>
#include <QTimer>
#include <QIODevice>
#include <QFile>

// OpenCV libs
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

// CaptureInputSource extends QThread
class CaptureInputSource : public QThread
{
    Q_OBJECT
public:
    //Mat to store image from camera
    Mat img, resizedImg;

    String inputSource = "";

    /*
     * Constructor to start single shot timer and connect the signal once every loop
     * in StartCam() slot
     */
    CaptureInputSource(String inputSource)
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

            img = Mat::zeros(Size(640, 480), CV_8UC3);
            resizedImg = Mat::zeros(Size(640, 480), CV_8UC3);

            //TODO: apply FPS
            while(1)
            {
                try {
                    double fps = cap.get(cv::CAP_PROP_FPS);
                    bool isSuccess = cap.read(img);

                    if(!Size(img.rows , img.rows).empty()) // Avoid empty image resizing error
                        resize(img, resizedImg, Size(640, 480));

                    if(!isSuccess)
                    {
                        SourceCaptureError("Cannot read the frame from the source");
                        //                        cap.open("/home/jairaj/Desktop/Projects/JAS.mp4");
                        openSource();
                        continue; // retry
                    }
                    //            img = loadFromQrc(":/test_file/cam_test_2.jpg");
                    //img = Mat::zeros(Size(640, 480), CV_8UC3); //Black for Simulation Purpose
                    emit SourceCaptured();
                    QThread::usleep(1000000/fps);
                } catch (cv::Exception& e) {
                    SourceCaptureError(e.what());
                }
            }
        }
        catch (cv::Exception& e) {
            SourceCaptureError(e.what());
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
        cout << "Path: " << inputSource << endl;
        cap.release();
        if(std::all_of(inputSource.begin(), inputSource.end(), ::isdigit)) // check if only contains digits
        {
            cap.open(stoi(inputSource)); // For Camera number
        }
        else
            cap.open(inputSource); // For file path
    }

private:

    VideoCapture cap;
    QTimer *start_cam_once_timer = new QTimer(this);

    //Function to convert QT res image file to OpenCV Mat object
    Mat loadFromQrc(QString qrc, int flag = IMREAD_COLOR)
    {
        //double tic = double(getTickCount());

        QFile file(qrc);
        Mat m;
        if(file.open(QIODevice::ReadOnly))
        {
            qint64 sz = file.size();
            std::vector<uchar> buf(sz);
            file.read((char*)buf.data(), sz);
            m = imdecode(buf, flag);
        }

        //double toc = (double(getTickCount()) - tic) * 1000.0 / getTickFrequency();
        //qDebug() << "OpenCV loading time: " << toc;

        return m;
    }
};

#endif // CAPTUREINPUTSOURCE_H
