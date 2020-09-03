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
#include <QScrollArea>
#include <QWindow>
#include <QFuture>
#include <QDateTime>

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
#include "OpenCVFunction/erodedilate.h"
#include "OpenCVFunction/cannyedge.h"
#include "OpenCVFunction/blur.h"
#include "OpenCVFunction/backgroundsubtract.h"
#include "OpenCVFunction/houghcircles.h"
#include "OpenCVFunction/houghlines.h"
#include "OpenCVFunction/histogram.h"
#include "OpenCVFunction/harriscornerdetector.h"
#include "OpenCVFunction/inrange.h"
#include "OpenCVFunction/erodedilate.h"
#include "OpenCVFunction/bitwiseops.h"
#include "OpenCVFunction/contours.h"

// Include all Custom Widgets here
#include "Window/AboutDialog/aboutdialog.h"
#include "CustomWidgets/HybridSlider/hybridslider.h"
#include "CustomWidgets/ErrorDialog/errordialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Types of Messages for User
enum MESSAGE_TYPE{INFO, ERROR, WARNING};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /**
     * @brief The OPCodes enum Enum for OpenCV Operations Base Config Widget
     *  To add a enum value see the note below
     */
    enum OPCodes{NO_OPERATION, COLOR_SPACES, IMAGE_FLIP, COLOR_PICKER, INRANGE,
                 CANNY_EDGE, BLUR, BKG_SUBTRACT, HOUGH_CIRCLES, HOUGH_LINES,
                 HISTOGRAM_CALCULATION, HARRIS_CORNER, ERODE, DILATE, BITWISE_OPS,
                 CONTOURS,

              /*
               * Add all other Enum values before this
               *
               * To connect OpenCV operation Base Config widget to
               * the added OpCodes enum, see MainWindow::addOperation(...)
               */
                 NONE /* Corresponds to OPCodes::NO_OPERATION */ };

private slots:
    void sourceRadioButtonClicked();
    void applySourceClicked();
    void browseClicked();
    void startRecClicked();
    void stopRecClicked();
    void captureClicked();
    void getSourceCaptureImage(cv::Mat originalImg);
    void showOperationalError(QString title, QString error);
    void toggleFlipSource(bool);
    void addOperation(MainWindow::OPCodes opCode = NO_OPERATION);
    void lastOperationChanged(MainWindow::OPCodes opCode);
    void showAboutDialog();
    void outputLabelLBClicked(QPoint);
    void showHideExplodedView(int);
    void refreshOutputImage(const cv::Mat img);
    void addOperationWidget();
    void removeOperationWidget();
    void refreshOperationWidgets();
    void switchThemeButtonClicked();
    void operationSelectedToDisplay(ParamAdjustWidget*);
    void updateExplodedView(QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>>);

signals:
    void refreshOutputImageSignal(cv::Mat);
    void removeOperationWidgetSignal();
    void showErrorDialog(QString, QString);
    void updateExplodedViewSignal(QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>>);
    void updateFPSLabel(int fps);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMutex qmutex;

    QFuture<void> chainProcessFuture;

    bool chainMenuInitDone = false;

    void initUI();

    void connectSignals();

    CaptureInputSource* captureInputSource = nullptr;
    qint64 prevOutputTime = -1;
    qint64 prevOutputFPSShowTime = -1;
    QPair<int, double> aggregateOutputFPS = qMakePair(0, 0);
    void updateOutputFPS();

    AboutDialog* aboutDialog = nullptr;

    QList<BaseConfigWidget*> baseConfigWidgetChain;

    bool isSourceFlipped = false;

    const int continuousErrorThreshold = 5;
    int continuousErrorCount = 0;

    void refreshInputImage(cv::Mat img);
    QTimer* userMsgTimer = new QTimer(this);
    void setUserMessage(QString message, MESSAGE_TYPE);

    QTimer* ioMsgTimer = new QTimer(this);
    void ioErrorMessage(QString message);
    ErrorDialog* errorDialog = new ErrorDialog();

    void waitForChainProcessing();

    QWidget *chainMenuSubWgt = new QWidget();
    QVBoxLayout *chainMenuVBox = new QVBoxLayout(chainMenuSubWgt);

    QButtonGroup* chainMenuRadioButtonsGroup = new QButtonGroup();

    QWidget *wgtSubtest = new QWidget();
    QVBoxLayout* testVBox = new QVBoxLayout(wgtSubtest);

    QString exportFolderPath = "";
    QPixmap inputPixMap;
    QPixmap outputPixMap;
    bool isRecording = false;

    QWidget *client = new QWidget;
    QScrollArea *scrollArea = new QScrollArea;
    QGridLayout *loGrid = new QGridLayout;
    QTabWidget *tabPage = new QTabWidget;
    QWidget *pageWidget = new QWidget;

    int explodedViewState = 0;

    /*
     * overriden closeEvent to close all opened windows when MainWindow
     * closeEvent(...) is fired
     */
    void closeEvent ([[maybe_unused]] QCloseEvent *event) override
    {
        if(aboutDialog != nullptr)
        {
            /*
             * Call close() on all Windows/Dialogs apart from MainWindow here
             */
            aboutDialog->close();
        }
        errorDialog->close();
    }

    cv::VideoWriter inputVideo, outputVideo;

    void writeToVideo(cv::VideoWriter, cv::Mat);

    QString exportButtonsStyleSheet = "QToolButton"
                                      "{"
                                      "  background-color: transparent;"
                                      "  border-image: url(:/assets/%1.png);"
                                      "  background: none;"
                                      "  border: none;"
                                      "  background-repeat: none;"
                                      "}"
                                      "QToolButton:pressed"
                                      "{"
                                      "  background-color: transparent;"
                                      "  border-image: url(:/assets/%2.png);"
                                      "  background: none;"
                                      "  border: none;"
                                      "  background-repeat: none;"
                                      "}"
                                      "QToolButton:disabled"
                                      "{"
                                      "  background-color: transparent;"
                                      "  border-image: url(:/assets/%3.png);"
                                      "  background: none;"
                                      "  border: none;"
                                      "  background-repeat: none;"
                                      "}";
};
