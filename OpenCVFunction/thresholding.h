#ifndef THRESHOLDING_H
#define THRESHOLDING_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "Utils/baseconfigwidget.h"
#include "OpenCVFunction/colorspaces.h"

class Thresholding : public ColorSpace
{
    Q_OBJECT
public:
    Thresholding()
    {
        operationName = "Thresholding";
        // TODO
        moreInfoLink = "TODO";
        this->initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)
    {
        cv::Mat outputImage = ColorSpace::getProcessedImage(inputImage);

        // TODO: Apply Threshold values from UI

        return outputImage;
    }

    ~Thresholding()
    {
        printf("Thresholding destroyed\n");
    }

private:
    void initWidget()
    {
    }
};


#endif // THRESHOLDING_H
