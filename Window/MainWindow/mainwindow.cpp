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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Utils/constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();

    // FIXME: Check FIXME in HybridSlider cpp source
    //    HybridSlider* hybrid = new HybridSlider();
    //    hybrid->show();

    connect(ui->cameraRadioButton,SIGNAL(clicked()),this,SLOT(sourceRadioButtonClicked()));
    connect(ui->fileRadioButton,SIGNAL(clicked()),this,SLOT(sourceRadioButtonClicked()));
    connect(ui->buttonSelectSource,SIGNAL(released()),this,SLOT(sourceSelectClicked()));
    connect(ui->checkBoxMirror, SIGNAL(clicked(bool)), this, SLOT(toggleFlipSource(bool)));
    connect(ui->buttonBrowse,SIGNAL(released()),this,SLOT(browseClicked()));
    connect(ui->buttonMoreInfo,SIGNAL(released()),this,SLOT(moreInfoOperationClicked()));
    connect(ui->buttonExplodedView,SIGNAL(released()),this,SLOT(showHideExplodedView()));

    connect(ui->actionAbout, &QAction::triggered, this,
            [=]() {
        showAboutDialog();
    });

    connect(ui->actionColorSpace, &QAction::triggered, this,
            [=]() {
        operationSelected(COLOR_SPACES);
    });

    connect(ui->actionColorSpace, &QAction::triggered, this,
            [=]() {
        operationSelected(COLOR_SPACES);
    });
    connect(ui->actionImage_Flip, &QAction::triggered, this,
            [=]() {
        operationSelected(IMAGE_FLIP);
    });
    connect(ui->actionColor_Picker, &QAction::triggered, this,
            [=]() {
        operationSelected(COLOR_PICKER);
    });
    connect(ui->actionThresholding, &QAction::triggered, this,
            [=]() {
        operationSelected(THRESHOLDING);
    });
    connect(ui->actionCanny_Edge, &QAction::triggered, this,
            [=]() {
        operationSelected(CANNY_EDGE);
    });
    connect(ui->actionBlur, &QAction::triggered, this,
            [=]() {
        operationSelected(BLUR);
    });
    connect(ui->actionMotion_detection, &QAction::triggered, this,
            [=]() {
        operationSelected(BKG_SUBTRACT);
    });
    connect(ui->actionHough_Circles, &QAction::triggered, this,
            [=]() {
        operationSelected(HOUGH_CIRCLES);
    });
    connect(ui->actionHough_Lines, &QAction::triggered, this,
            [=]() {
        operationSelected(HOUGH_LINES);
    });
    connect(ui->actionHistogram, &QAction::triggered, this,
            [=]() {
        operationSelected(HISTOGRAM_CALCULATION);
    });

    connect(ui->labelOutput, SIGNAL(LBclicked(int, int)), this, SLOT(outputLabelLBClicked(int, int)));
}

void MainWindow::initUI(){
    this->setWindowTitle(Info::appName);
    this->setWindowIcon(QIcon(":/assets/app_logo.png"));

    QButtonGroup* group = new QButtonGroup();
    group->addButton(ui->cameraRadioButton);
    group->addButton(ui->fileRadioButton);

    sourceRadioButtonClicked();

    setUserMessage("Initializing Done", INFO);
}

void MainWindow::operationSelected(int opCode)
{
    baseConfigWidget->setExplodedView(false);

    // FIXME: Many operations are slow in OpenCV 4.x with Ubuntu 20.04: Reason unknown

    switch (opCode) {
    case COLOR_SPACES:
        baseConfigWidget = new ColorSpace();
        break;
    case IMAGE_FLIP:
        baseConfigWidget = new ImageFlip();
        break;
    case COLOR_PICKER:
        baseConfigWidget = new ColorPicker();
        break;
    case CANNY_EDGE:
        baseConfigWidget = new CannyEdge();
        break;
    case THRESHOLDING:
        baseConfigWidget = new Thresholding();
        break;
    case BLUR:
        baseConfigWidget = new Blur();
        break;
    case BKG_SUBTRACT:
        baseConfigWidget = new BackgroundSubtraction();
        break;
    case HOUGH_CIRCLES:
        baseConfigWidget = new HoughCircles();
        break;
    case HOUGH_LINES:
        baseConfigWidget = new HoughLines();
        break;
    case HISTOGRAM_CALCULATION:
        baseConfigWidget = new HistogramCalculation();
        break;
    }

    ui->labelOperationName->setText(baseConfigWidget->getOperationName());
    QWidget *configWidget = baseConfigWidget->getConfigWidget();
    ui->scrollArea->setWidget(configWidget);
}

void MainWindow::showHideExplodedView()
{
    if(baseConfigWidget->isExplodedViewEnabled())
    {
        if(baseConfigWidget->setExplodedView(true))
        {
            // TODO: Change Icon to minimize
        }
    }
    else
    {
        baseConfigWidget->setExplodedView(false);
        // TODO: Change Icon to exploded
    }

}

void MainWindow::showAboutDialog()
{
    if(aboutDialog != nullptr)
    {
        if(!aboutDialog->isVisible())
        {
            // Set About Dialog Window Position and Always on Top
            QPoint mainWindowCenter = getWindowCenter();
            QPoint aboutDialogHalfSize = QPoint(aboutDialog->geometry().width()/2,
                                                aboutDialog->geometry().height()/2);
            aboutDialog->move(mainWindowCenter - aboutDialogHalfSize);
            aboutDialog->show();
        }
        else // If dialog is already visible but not in focus
        {
            aboutDialog->raise();
            aboutDialog->activateWindow();
        }
    }
    else // If AboutDialog object holds nullptr which is what it is initialized with
    {
        aboutDialog = new AboutDialog(this);
        showAboutDialog();
    }
}

void MainWindow::GetSourceCaptureImage()
{
    cv::Mat capturedReziedImg = captureInputSource->resizedImg;
    cv::Mat capturedOriginalImg = captureInputSource->img;

    if(isSourceFlipped)
    {
        cv::flip(capturedReziedImg, capturedReziedImg, 1);
        cv::flip(capturedOriginalImg, capturedOriginalImg, 1);
    }

    RefreshInputImage(capturedReziedImg);
    RefreshOutputImage(capturedOriginalImg);
}

void MainWindow::GetSourceCaptureError(QString error)
{
    setUserMessage(error, ERROR);
}

void MainWindow::RefreshInputImage(cv::Mat img)
{
    try
    {
        cv::Mat inputImage;
        cvtColor(img, inputImage, cv::COLOR_BGR2RGB);
        cv::resize(inputImage, inputImage, cv::Size(320, 240));

        QPixmap OpenCV2QTOP = QPixmap::fromImage(
                    QImage(
                        inputImage.data, inputImage.cols,
                        inputImage.rows, inputImage.step,
                        QImage::Format_RGB888));

        ui->labelInput->setPixmap(OpenCV2QTOP);
    }

    catch(cv::Exception& e)
    {
        captureInputSource->resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    }
}

void MainWindow::RefreshOutputImage(cv::Mat img)
{
    cv::Mat outputImg = baseConfigWidget->getProcessedImage(img);
    try
    {
        cvtColor(outputImg, outputImg, cv::COLOR_BGR2RGB);
        QPixmap OpenCV2QTOP = QPixmap::fromImage(
                    QImage(
                        outputImg.data, outputImg.cols,
                        outputImg.rows, outputImg.step,
                        QImage::Format_RGB888));

        ui->labelOutput->setPixmap(OpenCV2QTOP);
    }

    catch(cv::Exception& e)
    {
        captureInputSource->resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    }
}

void MainWindow::sourceRadioButtonClicked(){
    if(ui->cameraRadioButton->isChecked())
    {
        ui->buttonBrowse->hide();
        ui->labelCameraIndex->show();
        ui->textInputSource->setPlainText("0");
    }
    else if(ui->fileRadioButton->isChecked())
    {
        ui->buttonBrowse->show();
        ui->labelCameraIndex->hide();
        ui->textInputSource->setPlainText("Video/Image file path...");
    }
}

void MainWindow::browseClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(filePath.length() > 0)
        ui->textInputSource->setPlainText(filePath);
}

void MainWindow::sourceSelectClicked()
{
    std::cout << "Source Select Clicked!!" << std::endl;
    QString path = ui->textInputSource->toPlainText();
    if(ui->fileRadioButton->isChecked()){
        QFileInfo check_file(path);
        if (!(check_file.exists() && check_file.isFile()))
        {
            printf("Provided file does not exist\n");
            return;
        }
    }
    else
    {
        if (path == "")
        {
            printf("Camera Number not provided");
            return;
        }
    }

    if(!cam_thread->isRunning()){
        captureInputSource = new CaptureInputSource(path.toStdString());
        captureInputSource->moveToThread(cam_thread);
        // Start capture thread after confirming input source
        cam_thread->start();

        connect(captureInputSource, SIGNAL(SourceCaptured()), this, SLOT(GetSourceCaptureImage()));
        connect(captureInputSource, SIGNAL(SourceCaptureError(QString)), this, SLOT(GetSourceCaptureError(QString)));
    }
    else{
        std::cout << "Cam Thread already running!!" << std::endl;
        captureInputSource->inputSource = path.toStdString();
        captureInputSource->relesaseCap();
    }
}

void MainWindow::outputLabelLBClicked(int x, int y)
{
    baseConfigWidget->begin =cv::Point(x, y);
}

void MainWindow::moreInfoOperationClicked()
{
    QDesktopServices::openUrl(QUrl(baseConfigWidget->getInfoURL()));
}

void MainWindow::toggleFlipSource(bool isChecked)
{
    isSourceFlipped = isChecked;
}

void MainWindow::setUserMessage(QString message, MESSAGE_TYPE messageType)
{
    QPalette sample_palette;

    messageType == ERROR ? sample_palette.setColor(QPalette::WindowText, Qt::red):
                           messageType == WARNING ? sample_palette.setColor(QPalette::WindowText, Qt::yellow):
                                                    sample_palette.setColor(QPalette::WindowText, Qt::black);

    ui->labelUserMessage->setAutoFillBackground(true);
    ui->labelUserMessage->setPalette(sample_palette);
    ui->labelUserMessage->setText(message);
}

QPoint MainWindow::getWindowCenter()
{
    QPoint position = QPoint(0,0);
    position.setX(this->geometry().x() + this->geometry().width()/2);
    position.setY(this->geometry().y() + this->geometry().height()/2);
    return  position;
}

MainWindow::~MainWindow()
{
    delete ui;
}
