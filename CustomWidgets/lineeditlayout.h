#ifndef LINEEDITLAYOUT_H
#define LINEEDITLAYOUT_H

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QValidator>

class LineEditLayout: public QHBoxLayout
{
    Q_OBJECT

public:
    QLabel* titleLabel = new QLabel();
    QLineEdit* lineEdit = new QLineEdit();

    explicit LineEditLayout(QString title,
                            int initialValue,
                            int fixedWidth = 160,
                            int fixedHeight = 60,
                            QWidget* parent = Q_NULLPTR,
                            Qt::WindowFlags f = Qt::WindowFlags())
    {

    }
};

#endif // LINEEDITLAYOUT_H
