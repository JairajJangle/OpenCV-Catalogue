#ifndef DILATE_H
#define DILATE_H

// QT libs
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomWidgets/baseconfigwidget.h"

class Dilate : public BaseConfigWidget
{
    Q_OBJECT
public:
    Dilate()
    {
        operationName = "Dilate";
        moreInfoLink = "https://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#dilate";
        initWidget();
    }

    cv::Mat getProcessedImage(cv::Mat inputImage)try
    {
        cv::Mat outputImage;

        int erosion_size = 6;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS,
                              cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                              cv::Point(erosion_size, erosion_size) );

        cv::dilate(inputImage, outputImage, element);

//        dilate(inputImage, outputImage, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

        return outputImage;
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

protected:
    void initWidget()
    {
        BaseConfigWidget::initWidget();
    }
};

#endif // DILATE_H
