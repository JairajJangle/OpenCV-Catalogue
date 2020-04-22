#ifndef BASECONFIGWIDGET_H
#define BASECONFIGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <opencv2/opencv.hpp>

#include "CustomWidgets/ClickableLabel/clickablelabel.h"

using namespace cv;

class BaseConfigWidget
{
protected:
    QWidget* configWidget;
    QString operationName = "No operation Selected";
    QString moreInfoLink = "";
    ClickableLabel* labelInfo = new ClickableLabel();

public:
    BaseConfigWidget(){
        labelInfo->setText("More Info >>");
    }
    ~BaseConfigWidget(){}

    QWidget* getConfigWidget()
    {
        return configWidget;
    }

    QString getOperationName()
    {
        return operationName;
    }

    QString getInfoURL()
    {
        return moreInfoLink;
    }

    virtual Mat getProcessedImage(Mat inputImage){
        return inputImage;
    }
};

#endif // BASECONFIGWIDGET_H
