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

#ifndef THRESHOLDING_H
#define THRESHOLDING_H

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"

class Thresholding : public BaseConfigWidget
{
    Q_OBJECT
public:
    Thresholding()
    {
        operationName = "Thresholding";
        // TODO
        moreInfoLink = "TODO";
        this->initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        m.lock();

        m.unlock();
        return inputImage;
    }
    catch(cv::Exception& e){
        throw e;
    } catch(std::exception& e) {
        throw e;
    }
    catch(...){
    throw std::string("Unknown Exception in ")
    + std::string(typeid(this).name());
}

    ~Thresholding()
    {
        printf("Thresholding destroyed\n");
    }

private:
    void initWidget()
    {
        BaseConfigWidget::initWidget();
    }
};


#endif // THRESHOLDING_H
