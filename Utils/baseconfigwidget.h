#ifndef BASECONFIGWIDGET_H
#define BASECONFIGWIDGET_H

#include <iostream>

#include <opencv2/opencv.hpp>

// QT libs
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

// OpenCV libs

#include "CustomWidgets/ClickableLabel/clickablelabel.h"

class BaseConfigWidget
{
protected:
    QWidget* configWidget;
    QString operationName = "No operation Selected";
    QString moreInfoLink = "";
    ClickableLabel* labelInfo = new ClickableLabel();

    QScrollArea *scrl = new QScrollArea();

    QWidget *wgtMain = new QWidget();
    QWidget *wgtSub = new QWidget();

    QVBoxLayout *vboxMain = new QVBoxLayout(wgtMain);
    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

public:
    cv::Point begin;
    cv::Point end;

    BaseConfigWidget(){
        begin =cv::Point(-1, -1);
        end =cv::Point(-1, -1);
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

    virtual cv::Mat getProcessedImage(cv::Mat inputImage){
        return inputImage;
    }

    virtual void initWidget()
    {
        vboxMain->addWidget(wgtSub);
        scrl->setWidget(wgtMain);
        configWidget = scrl;
    }
};

#endif // BASECONFIGWIDGET_H
