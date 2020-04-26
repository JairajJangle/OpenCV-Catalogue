#ifndef EROSIONDILATION_H
#define EROSIONDILATION_H

/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "Utils/baseconfigwidget.h"

class ErosionDilation : public QWidget, public BaseConfigWidget
{
    Q_OBJECT
public:
    ErosionDilation()
    {
        operationName = "Erosion and Dilation";
        moreInfoLink = "https://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html";
        initWidget();
    }
};

#endif // EROSIONDILATION_H
