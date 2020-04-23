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
        emit LBclicked(event->x(), event->y());
    }
    if(event->button() == Qt::RightButton)
    {
        emit RBclicked(event->x(), event->y());
    }
}

//void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
//{
//    ClickPos = cv::Point(event->x(), event->y());
//    emit clicked();
//}
