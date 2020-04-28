#ifndef ERRORLABEL_H
#define ERRORLABEL_H

#include <QLabel>

class ErrorLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ErrorLabel(QString error = "", QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags())
    {
        this->setStyleSheet("QLabel { color : red; }");
        this->setText(error);
        QSizePolicy sp_retain = this->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        this->setSizePolicy(sp_retain);
    }
    void hide()
    {
        this->setVisible(false);
    }
    void show()
    {
        this->setVisible(true);
    }
    ~ErrorLabel()
    {

    }
};

#endif // ERRORLABEL_H
