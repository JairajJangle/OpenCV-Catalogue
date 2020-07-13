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

// Include all QT dependencies here
#include <QMainWindow>
#include <QThread>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <QButtonGroup>
#include <QCloseEvent>
#include <QMessageBox>
#include <QScrollBar>
#include <QtConcurrent/QtConcurrent>
#include <QGroupBox>
#include <QWindow>

// Include all Utils here
#include "Utils/captureinputsource.h"
#include "Utils/utils.h"

/*
 * Include OpenCV Operation Headers here
 * To add an operation refer to base class: CustomWidgets/baseconfigwidget.h
 */
#include "OpenCVFunction/colorspaces.h"
#include "OpenCVFunction/imageflip.h"
#include "OpenCVFunction/colorpicker.h"
#include "OpenCVFunction/dilate.h"
#include "OpenCVFunction/cannyedge.h"
#include "OpenCVFunction/blur.h"
#include "OpenCVFunction/backgroundsubtract.h"
#include "OpenCVFunction/houghcircles.h"
#include "OpenCVFunction/houghlines.h"
#include "OpenCVFunction/histogram.h"
#include "OpenCVFunction/harriscornerdetector.h"
#include "OpenCVFunction/inrange.h"
#include "OpenCVFunction/dilate.h"

// Include all Custom Widgets here
#include "Window/AboutDialog/aboutdialog.h"
#include "CustomWidgets/HybridSlider/hybridslider.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Types of Messages for User
enum MESSAGE_TYPE{INFO, ERROR, WARNING};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum OPCodes{NO_OPERATION, COLOR_SPACES, IMAGE_FLIP, COLOR_PICKER, INRANGE,
                 CANNY_EDGE, BLUR, BKG_SUBTRACT, HOUGH_CIRCLES, HOUGH_LINES,
                 HISTOGRAM_CALCULATION, HARRIS_CORNER, DILATE,

                 /* Add all other Enum values before this */
                 NONE /* Corresponds to No Operation itself */ };

private slots:
    void sourceRadioButtonClicked();
    void applySourceClicked();
    void browseClicked();
    void getSourceCaptureImage();
    void getSourceCaptureError(QString);
    void toggleFlipSource(bool);
    void addOperation(MainWindow::OPCodes opCode = NO_OPERATION);
    void lastOperationChanged(MainWindow::OPCodes opCode);
    void showAboutDialog();
    void outputLabelLBClicked(int x, int y);
    void showHideExplodedView();
    void refreshOutputImage(const cv::Mat img);
    void addOperationWidget();
    void removeOperationWidget();
    void refreshOperationWidgets();
    void switchThemeButtonClicked();
    void operationSelectedToDisplay(ParamAdjustWidget*);

signals:
    void refreshOutputImageSignal(cv::Mat);
    void removeOperationWidgetSignal();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMutex qmutex;

    bool chainMenuInitDone = false;

    void initUI();
    void closeEvent ([[maybe_unused]] QCloseEvent *event) override
    {
        if(aboutDialog != nullptr)
        {
            aboutDialog->close();
        }
    }

    CaptureInputSource* captureInputSource = nullptr;

    AboutDialog* aboutDialog = nullptr;

    QList<BaseConfigWidget*> baseConfigWidgetChain;

    bool isSourceFlipped = false;

    void refreshInputImage(cv::Mat img);
    void setUserMessage(QString message, MESSAGE_TYPE);

    QWidget *wgtSub = new QWidget();
    QVBoxLayout *vBoxSub = new QVBoxLayout(wgtSub);

    // TODO: Add and test Chain Menu Radio buttons grouped working
    QButtonGroup* chainMenuRadioButtonsGroup = new QButtonGroup();

    QWidget *wgtSubtest = new QWidget();
    QVBoxLayout* testVBox = new QVBoxLayout(wgtSubtest);
};
