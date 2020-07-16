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

#include <QWidget>
#include <QRadioButton>
#include <QComboBox>

#include "Utils/utils.h"

namespace Ui {
class ChainMenuWidget;
}

class ChainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChainMenuWidget(QWidget *parent = nullptr);

    /**
     * @brief setAddButonEnabled Enable or Disable Add (+) button
     * @param enabled Flag to change the state
     */
    void setAddButonEnabled(bool enabled);

    /**
     * @brief setRemoveButtonEnabled Enable or Disable Remove (-) button
     * @param enabled Flag to change the state
     */
    void setRemoveButtonEnabled(bool enabled);

    /**
     * @brief setComboBoxEnabled Enable or Disable Drop Down Menu / Combo box
     * @param enabled Flag to change the state
     */
    void setComboBoxEnabled(bool enabled);
    // Enable or Disable the whole ChainMenuWidget Widget
    void setEnabled(bool enabled);
    /**
     * Change the current operation displayed in Combo box
     * @param operationName takes the name of operation that
     * is to be displayed in the Combo box
     */
    void setCurrentOperation(QString operationName);
    /**
     * Set visibility of vertical "linking" line
     * Refer the .ui file
     */
    void setLineVisibility(bool visible);
    // Change style sheet, called when application theme changes
    void setStyleSheet(bool isDarkMode);
    // Returns the operation selection Radio button
    QRadioButton* getRadioButton();

    ~ChainMenuWidget();

signals:
    void addOperationClicked();
    void removeOperationClicked();
    void operationChanged(int index);
    void radioButtonChecked();

private:
    Ui::ChainMenuWidget *ui;

    const QString buttonAddLightStyle = QString("QToolButton#buttonAdd"
                                                "{"
                                                "    color: green;"
                                                "}"
                                                "QToolButton:disabled#buttonAdd"
                                                "{"
                                                "    color: #787878;"
                                                "}");

    const QString buttonAddDarkStyle = QString("QToolButton#buttonAdd"
                                               "{"
                                               "    color: #22ff00;"
                                               "}"
                                               "QToolButton:disabled#buttonAdd"
                                               "{"
                                               "    color: #787878;"
                                               "}");

    const QString buttonRemoveLightStyle = QString("QToolButton#buttonRemove "
                                                   "{"
                                                   "    color: red;"
                                                   "}"
                                                   "QToolButton:disabled#buttonRemove"
                                                   "{"
                                                   "    color: #787878;"
                                                   "}");

    const QString buttonRemoveDarkStyle = QString("QToolButton#buttonRemove "
                                                  "{"
                                                  "    color: #ff2a00;"
                                                  "}"
                                                  "QToolButton:disabled#buttonRemove"
                                                  "{"
                                                  "    color: #787878;"
                                                  "}");
};
