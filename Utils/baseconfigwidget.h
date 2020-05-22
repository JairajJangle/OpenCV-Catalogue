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
private:
    QScrollArea *scrl = new QScrollArea();
    QWidget *wgtSub = new QWidget();

protected:
    QWidget *wgtMain = new QWidget();

    QWidget* configWidget;
    QString operationName = "No operation Selected";
    QString moreInfoLink = "";
    ClickableLabel* labelInfo = new ClickableLabel();

    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

private:
    QVBoxLayout *vboxMain = new QVBoxLayout(wgtMain);

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
