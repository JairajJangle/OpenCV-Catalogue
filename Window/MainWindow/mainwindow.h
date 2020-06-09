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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <QButtonGroup>
#include <QCloseEvent>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QGroupBox>
#include <QWindow>

#include <iostream>

#include "Utils/captureinputsource.h"
#include "Utils/utils.h"

#include "OpenCVFunction/colorspaces.h"
#include "OpenCVFunction/imageflip.h"
#include "OpenCVFunction/colorpicker.h"
#include "OpenCVFunction/erosiondilation.h"
#include "OpenCVFunction/thresholding.h"
#include "OpenCVFunction/cannyedge.h"
#include "OpenCVFunction/blur.h"
#include "OpenCVFunction/backgroundsubtract.h"
#include "OpenCVFunction/houghcircles.h"
#include "OpenCVFunction/houghlines.h"
#include "OpenCVFunction/histogram.h"
#include "OpenCVFunction/harriscornerdetector.h"

#include "Window/AboutDialog/aboutdialog.h"

#include "CustomWidgets/HybridSlider/hybridslider.h"
#include "CustomWidgets/Collapsible/collapsible.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum MESSAGE_TYPE{INFO, ERROR, WARNING};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum OPCodes{NONE, COLOR_SPACES, IMAGE_FLIP, COLOR_PICKER, THRESHOLDING,
                 CANNY_EDGE, BLUR, BKG_SUBTRACT, HOUGH_CIRCLES, HOUGH_LINES,
                 HISTOGRAM_CALCULATION, HARRIS_CORNER};

private slots:
    void sourceRadioButtonClicked();
    void sourceSelectClicked();
    void browseClicked();
    void GetSourceCaptureImage();
    void GetSourceCaptureError(QString);
    void toggleFlipSource(bool);
    void moreInfoOperationClicked();
    void addOperation(OPCodes opCode = NONE);
    void lastOperationChanged(OPCodes opCode);
    void showAboutDialog();
    void outputLabelLBClicked(int x, int y);
    void showHideExplodedView();
    void refreshOutputImage(const cv::Mat img);
    void addOperationWidget();
    void removeOperationWidgets();
    void refreshOperationWidgets();

signals:
    void refreshOutputImageSignal(cv::Mat);
    void paramWidgetSetSignal(bool isWidgetRemoved);
    void removeOperationWidgetsSignal();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QScrollArea* noOperationWidget = new QScrollArea();

    Ui::MainWindow *ui;

    QThread *cam_thread = new QThread;
    CaptureInputSource* captureInputSource;

    AboutDialog* aboutDialog = nullptr;

    QList<BaseConfigWidget*> baseConfigWidgetChain;

    bool isSourceFlipped = false;

    void initUI();

    void refreshInputImage(cv::Mat img);
    void setUserMessage(QString message, MESSAGE_TYPE);

    void closeEvent (QCloseEvent *event) override
    {
        if(aboutDialog != nullptr)
        {
            aboutDialog->close();
        }
    }

    QWidget *wgtSub = new QWidget();
    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

    // TODO: Add and test Chain Menu Radio buttons grouped working
    QGroupBox* chainMenuRadioButtonsGroup = new QGroupBox();
        QVBoxLayout* testVBox = new QVBoxLayout();
    void configChainMenuList();
};
#endif // MAINWINDOW_H
