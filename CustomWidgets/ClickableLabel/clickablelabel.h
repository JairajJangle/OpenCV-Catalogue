/*
 * @author JairajJangle
 * @email jairaj.jangle@gmail.com
 */

// Customized Label class
#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QMouseEvent>

//A Custom Label Class inheriting QLabel
// Inherits QLabel with adding mousePressEvent overriden function to return mouse position
class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void LBclicked(int, int);
    void RBclicked(int, int);

protected:
    void mousePressEvent(QMouseEvent* event);
    //    void mouseMoveEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
