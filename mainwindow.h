#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>

#include <iostream>

#include "Utils/captureinputsource.h"
#include "OpenCVFunction/colorspaces.h"
#include "OpenCVFunction/imageflip.h"
#include "OpenCVFunction/colorpicker.h"

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
    void outputLabelLBClicked(int x, int y);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum OPCodes{COLOR_SPACES, IMAGE_FLIP, COLOR_PICKER};

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
