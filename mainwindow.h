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

using namespace std;

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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum OPCodes{COLOR_SPACES, THRESHOLDING};

    Ui::MainWindow *ui;

    QThread *cam_thread = new QThread;
    CaptureInputSource* captureInputSource;

    BaseConfigWidget* baseConfigWidget = new BaseConfigWidget;
    ColorSpace colorSpace;

    bool isSourceFlipped = false;

    void initUI();

    void RefreshInputImage(Mat img);
    void RefreshOutputImage(Mat img);
    void setUserMessage(QString message, MESSAGE_TYPE);
};
#endif // MAINWINDOW_H
