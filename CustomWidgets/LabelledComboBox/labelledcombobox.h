#pragma once

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QMap>

class LabelledComboBox : public QHBoxLayout
{
    Q_OBJECT

private:
    QLabel* titleLabel = new QLabel();

public:
    QComboBox* comboBox = new QComboBox();
    explicit LabelledComboBox(QString title,
                              QMap<QString, QVariant> nameValueMap,
                              int comboBoxFixedWidth = 100,
                              int labelFixedWidth = 100,
                              QWidget *parent = nullptr)
        :QHBoxLayout(parent)
    {
        titleLabel->setText(title);
        titleLabel->setFixedWidth(labelFixedWidth);
        titleLabel->setAlignment(Qt::AlignCenter);

        QMapIterator<QString, QVariant> i(nameValueMap);
        while (i.hasNext())
        {
            i.next();
            comboBox->addItem(i.key(), i.value());
        }

        comboBox->setFixedWidth(comboBoxFixedWidth);

        this->addWidget(titleLabel);

        this->addStretch();
        this->addWidget(comboBox);
        this->addStretch();
    }
};

