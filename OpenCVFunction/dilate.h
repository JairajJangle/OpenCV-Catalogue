#ifndef DILATE_H
#define DILATE_H

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"

class Dilate : public BaseConfigWidget
{
    Q_OBJECT
public:
    Dilate()
    {
        operationName = "Dilate";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#dilate";
        initWidget();
    }
};

#endif // DILATE_H
