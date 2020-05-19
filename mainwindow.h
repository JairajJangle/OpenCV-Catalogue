#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <QButtonGroup>

#include <iostream>

#include "Utils/captureinputsource.h"
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

#include "aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum MESSAGE_TYPE{INFO, ERROR, WARNING};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void sourceRadioButtonClicked();
    void sourceSelectClicked();
    void browseClicked();
    void GetSourceCaptureImage();
    void GetSourceCaptureError(QString);
    void toggleFlipSource(bool);
    void moreInfoOperationClicked();
    void operationSelected(int opCode);
    void showAboutDialog();
    void outputLabelLBClicked(int x, int y);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum OPCodes{COLOR_SPACES, IMAGE_FLIP, COLOR_PICKER, THRESHOLDING, EROSION_DILATION,
                 CANNY_EDGE, BLUR, BKG_SUBTRACT, HOUGH_CIRCLES, HOUGH_LINES,
                 HISTOGRAM_CALCULATION};

    Ui::MainWindow *ui;

    QThread *cam_thread = new QThread;
    CaptureInputSource* captureInputSource;

    BaseConfigWidget* baseConfigWidget = new BaseConfigWidget;

    bool isSourceFlipped = false;

    void initUI();

    void RefreshInputImage(cv::Mat img);
    void RefreshOutputImage(cv::Mat img);
    void setUserMessage(QString message, MESSAGE_TYPE);
};
#endif // MAINWINDOW_H
