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

#include "CustomWidgets/baseconfigwidget.h"

class WarpAffine : public BaseConfigWidget
{
    Q_OBJECT
public:
    WarpAffine()
    {
        operationName = "Warp Affine";
        moreInfoLink = "https://docs.opencv.org/4.5.2/da/d54/group__imgproc__transform.html#ga0203d9ee5fcd28d40dbc4a1ea4451983";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage) override try
    {
        srcTri[0] = cv::Point2f( 0.f, 0.f );
        srcTri[1] = cv::Point2f( inputImage.cols - 1.f, 0.f );
        srcTri[2] = cv::Point2f( 0.f, inputImage.rows - 1.f );

        dstTri[0] = cv::Point2f( 0.f, inputImage.rows*0.33f );
        dstTri[1] = cv::Point2f( inputImage.cols*0.85f, inputImage.rows*0.25f );
        dstTri[2] = cv::Point2f( inputImage.cols*0.15f, inputImage.rows*0.7f );

        cv::Mat warpMat = getAffineTransform(srcTri, dstTri);
        cv::Mat warpDst = cv::Mat::zeros(
                    inputImage.rows,
                    inputImage.cols,
                    inputImage.type()
                    );
        warpAffine(inputImage, warpDst, warpMat, warpDst.size());

        cv::Point center = cv::Point(warpDst.cols/2, warpDst.rows/2);
        double angle = -50.0;
        double scale = 0.6;

        cv::Mat rotMat = getRotationMatrix2D(center, angle, scale);

        cv::Mat warpRotateDst;
        warpAffine(warpDst, warpRotateDst, rotMat, warpDst.size());

        // TODO: Add Toggle to show warpRotateDst

        return warpDst;
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

private:
    cv::Point2f srcTri[3];
    cv::Point2f dstTri[3];

void initWidget() override
{
    BaseConfigWidget::initWidget();
}
};
