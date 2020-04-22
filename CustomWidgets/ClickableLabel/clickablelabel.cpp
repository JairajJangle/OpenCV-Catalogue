#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent)
{

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        ClickPos = cv::Point(event->x(), event->y());
        emit LBclicked();
    }
    if(event->button() == Qt::RightButton)
    {
        ClickPos = cv::Point(event->x(), event->y());
        emit RBclicked();
    }
}

//void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
//{
//    ClickPos = cv::Point(event->x(), event->y());
//    emit clicked();
//}
