/* OpenCV Catalogue is a desktop GUI application to showcase some OpenCV functions
 * and parameter adjustment using controls in GUI.
 * Copyright (C) 2020  Jairaj Jangle
 *
 * This file is part of OpenCV Catalogue.
 *
 * OpenCV Catalogue is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenCV Catalogue is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenCV Catalogue.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>

// Used in included files, do not remove
#include <QValidator>

/**
 * @brief The LineEditLayout class Cusotm Layout to show a labelled QLineEdit
 *  Consists for a Horizontal Layout with QLabel and a QLineEdit
 */
class LineEditLayout: public QHBoxLayout
{
    Q_OBJECT

private:
    QLabel* titleLabel = new QLabel();

public:
    QLineEdit* lineEdit = new QLineEdit();

    explicit LineEditLayout(QString title,
                            QVariant initialValue,
                            int lineEditFixedWidth = 100,
                            int labelFixedWidth = 100,
                            QWidget* parent = nullptr)
        :QHBoxLayout(parent)
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
