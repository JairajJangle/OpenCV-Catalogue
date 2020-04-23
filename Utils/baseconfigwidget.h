#ifndef BASECONFIGWIDGET_H
#define BASECONFIGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <opencv2/opencv.hpp>

// QT libs
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QLabel>
#include <QThread>
#include <QSizePolicy>
#include <QSpacerItem>

#include "CustomWidgets/ClickableLabel/clickablelabel.h"

using namespace cv;

class BaseConfigWidget
{
protected:
    QWidget* configWidget;
    QString operationName = "No operation Selected";
    QString moreInfoLink = "";
    ClickableLabel* labelInfo = new ClickableLabel();
    Point begin;
    Point end;

    QScrollArea *scrl = new QScrollArea();

    QWidget *wgtMain = new QWidget();
    QWidget *wgtSub = new QWidget();

    QVBoxLayout *vboxMain = new QVBoxLayout(wgtMain);
    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

public:
    BaseConfigWidget(){
        begin = Point(-1, -1);
        end = Point(-1, -1);
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

    virtual void initWidget()
    {
        vboxMain->addWidget(wgtSub);
        scrl->setWidget(wgtMain);
        configWidget = scrl;
    }
};

#endif // BASECONFIGWIDGET_H
