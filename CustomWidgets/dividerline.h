#ifndef HDIVIDERLINE_H
#define HDIVIDERLINE_H

#include <QFrame>

class DividerLine : public QFrame
{
public:

    explicit DividerLine(QWidget* parent = Q_NULLPTR,
                         Qt::WindowFlags f = Qt::WindowFlags())
    {
        this->setObjectName(QString::fromUtf8("line"));
        this->setGeometry(QRect(320, 150, 118, 3));
        this->setFrameShape(QFrame::HLine);
        this->setFrameShadow(QFrame::Sunken);
        this->setFixedHeight(20);
    }
};

#endif // HDIVIDERLINE_H
