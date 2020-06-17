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

#ifndef CHAINMENUWIDGET_H
#define CHAINMENUWIDGET_H

#include <QWidget>
#include <QPair>
#include <QRadioButton>

#include "Utils/utils.h"

namespace Ui {
class ChainMenuWidget;
}

class ChainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChainMenuWidget(QWidget *parent = nullptr);

    void setAddButonEnabled(bool enabled);
    void setRemoveButtonEnabled(bool enabled);
    void setComboBoxEnabled(bool enabled);
    void setEnabled(bool enabled);
    void setCurrentOperation(QString operationName);
    void setLineVisibility(bool visible);
    QRadioButton* getRadioButton();

    ~ChainMenuWidget();

signals:
    void addOperationClicked();
    void removeOperationClicked();
    void operationChanged(int index);
    void radioButtonChecked();

private:
    Ui::ChainMenuWidget *ui;
};

#endif // CHAINMENUWIDGET_H
