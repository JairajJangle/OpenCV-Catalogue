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
                            QVariant initialValue,
                            int lineEditFixedWidth = 100,
                            int labelFixedWidth = 100,
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
        titleLabel->setFixedWidth(labelFixedWidth);
        titleLabel->setAlignment(Qt::AlignCenter);

        lineEdit->setText(initialValue.toString());
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

    void setText(QString text)
    {
        lineEdit->setText(text);
    }

    void setText(int integerNumber)
    {
        lineEdit->setText(QString::number((integerNumber)));
    }

    void setText(QVariant text)
    {
        lineEdit->setText(text.toString());
    }

    void setText(double decimalNumber)
    {
        lineEdit->setText(QString::number((decimalNumber)));
    }

    void setVisible(bool visible)
    {
        titleLabel->setVisible(visible);
        lineEdit->setVisible(visible);
    }
};

#endif // LINEEDITLAYOUT_H
