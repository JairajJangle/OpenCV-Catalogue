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
                            int lineEditFixedWidth = 100,
                            int lineEditFixedHeight = 60,
                            QWidget* parent = Q_NULLPTR,
                            Qt::WindowFlags f = Qt::WindowFlags())
    {
        QSizePolicy sp_retainTitle = titleLabel->sizePolicy();
        sp_retainTitle.setRetainSizeWhenHidden(true);
        titleLabel->setSizePolicy(sp_retainTitle);
        QSizePolicy sp_retainValue = lineEdit->sizePolicy();
        sp_retainValue.setRetainSizeWhenHidden(true);
        lineEdit->setSizePolicy(sp_retainValue);

        titleLabel->setText(title);

        lineEdit->setText(QString::number(initialValue));
        lineEdit->setFixedWidth(lineEditFixedWidth);
        lineEdit->setAlignment(Qt::AlignCenter);

        this->addWidget(titleLabel);

        this->addStretch();
        this->addWidget(lineEdit);
        this->addStretch();
    }

    QString getText()
    {
        return lineEdit->text();
    }

    void setVisible(bool visible)
    {
        titleLabel->setVisible(visible);
        lineEdit->setVisible(visible);
    }
};

#endif // LINEEDITLAYOUT_H
