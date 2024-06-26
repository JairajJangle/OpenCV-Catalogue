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
#include <QWidget>
#include <QMouseEvent>


/**
 * @brief The ClickableLabel class Custom Label Class inheriting QLabel
 *  To emit signal when there are Mouse events on this widget
 */
class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr);
    ~ClickableLabel();

signals:
    /**
     * @brief LBclicked Signal fired when Left Mouse Button clicked
     */
    void LBclicked(QPoint);

    /**
     * @brief LBclicked Signal fired when Right Mouse Button clicked
     */
    void RBclicked(QPoint);

    /**
     * @brief LBMoved Signal fired when Left Mouse Button is dragged and moved
     */
    void LBMoved(QPoint);

    /**
     * @brief LBReleased Signal fired when Left Mouse Button is released after a move
     */
    void LBReleased(QPoint);

protected:
    /**
     * @brief mousePressEvent Overriden method from QLabel
     * @param event See QLabel::mousePressEvent
     */
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    bool ismouseLBMoved = false;
};
