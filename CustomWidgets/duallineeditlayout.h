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

class DualLineEditLayout: public QHBoxLayout
{
    Q_OBJECT

private:
    QLabel* titleLabel = new QLabel();

public:
    QPair<QLineEdit*, QLineEdit*> lineEdits =  qMakePair(new QLineEdit(), new QLineEdit());

    explicit DualLineEditLayout(QString title,
                                QPair<QVariant, QVariant> initialValues,
                                int lineEditFixedWidth = 100,
                                int labelFixedWidth = 100,
                                QWidget* parent = nullptr)
        :QHBoxLayout(parent)
    {
        QSizePolicy sp_retainTitle = titleLabel->sizePolicy();
        sp_retainTitle.setRetainSizeWhenHidden(true);
        titleLabel->setSizePolicy(sp_retainTitle);
        QSizePolicy sp_retainValue = lineEdits.first->sizePolicy();
        sp_retainValue.setRetainSizeWhenHidden(true);
        lineEdits.first->setSizePolicy(sp_retainValue);
        lineEdits.second->setSizePolicy(sp_retainValue);

        titleLabel->setText(title);
        titleLabel->setFixedWidth(labelFixedWidth);
        titleLabel->setAlignment(Qt::AlignCenter);

        lineEdits.first->setText(initialValues.first.toString());
        lineEdits.second->setText(initialValues.second.toString());
        lineEdits.first->setFixedWidth(lineEditFixedWidth);
        lineEdits.second->setFixedWidth(lineEditFixedWidth);
        lineEdits.first->setAlignment(Qt::AlignCenter);
        lineEdits.second->setAlignment(Qt::AlignCenter);

        this->addWidget(titleLabel);

        this->addStretch();
        this->addWidget(new QLabel(" ( "));
        this->addWidget(lineEdits.first);
        this->addWidget(new QLabel(" , "));
        this->addWidget(lineEdits.second);
        this->addWidget(new QLabel(" ) "));
        this->addStretch();
    }

    QPair<QString, QString> getTexts()
    {
        return qMakePair(lineEdits.first->text(),
                         lineEdits.second->text());
    }

    void setText(QPair<QVariant, QVariant> texts)
    {
        lineEdits.first->setText(texts.first.toString());
        lineEdits.second->setText(texts.second.toString());
    }

    void setVisible(bool visible)
    {
        titleLabel->setVisible(visible);
        lineEdits.first->setVisible(visible);
        lineEdits.second->setVisible(visible);
    }
};
