#ifndef HOUGHCIRCLEDETECTOR_H
#define HOUGHCIRCLEDETECTOR_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QRadioButton>

#include "Utils/baseconfigwidget.h"

class HoughCircleDetector: public QWidget, public BaseConfigWidget
{
    Q_OBJECT

public:
    HoughCircleDetector()
    {
        operationName = "Hough Circle Detector";
        moreInfoLink = "https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html";
        initWidget();
    }
};

#endif // HOUGHCIRCLEDETECTOR_H
