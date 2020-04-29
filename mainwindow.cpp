#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();

    connect(ui->cameraRadioButton,SIGNAL(clicked()),this,SLOT(sourceRadioButtonClicked()));
    connect(ui->fileRadioButton,SIGNAL(clicked()),this,SLOT(sourceRadioButtonClicked()));
    connect(ui->buttonSelectSource,SIGNAL(released()),this,SLOT(sourceSelectClicked()));
    connect(ui->checkBoxMirror, SIGNAL(clicked(bool)), this, SLOT(toggleFlipSource(bool)));
    connect(ui->buttonBrowse,SIGNAL(released()),this,SLOT(browseClicked()));
    connect(ui->buttonMoreInfo,SIGNAL(released()),this,SLOT(moreInfoOperationClicked()));

    connect(ui->actionColorSpace, &QAction::triggered,
            [=]() {
        emit operationSelected(COLOR_SPACES);
    });
    connect(ui->actionImage_Flip, &QAction::triggered,
            [=]() {
        emit operationSelected(IMAGE_FLIP);
    });
    connect(ui->actionColor_Picker, &QAction::triggered,
            [=]() {
        emit operationSelected(COLOR_PICKER);
    });
    connect(ui->actionThresholding, &QAction::triggered,
            [=]() {
        emit operationSelected(THRESHOLDING);
    });
    connect(ui->actionCanny_Edge, &QAction::triggered,
            [=]() {
        emit operationSelected(CANNY_EDGE);
    });
    connect(ui->actionBlur, &QAction::triggered,
            [=]() {
        emit operationSelected(BLUR);
    });

    connect(ui->labelOutput, SIGNAL(LBclicked(int, int)), this, SLOT(outputLabelLBClicked(int, int)));
}

void MainWindow::initUI(){
    this->setWindowTitle("OpenCV Catalogue");
    this->setWindowIcon(QIcon(":/assets/opencv_logo.png"));

    QButtonGroup* group = new QButtonGroup();
    group->addButton(ui->cameraRadioButton);
    group->addButton(ui->fileRadioButton);

    sourceRadioButtonClicked();

    setUserMessage("Initializing Done", INFO);
}

void MainWindow::operationSelected(int opCode)
{
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
    }

    ui->labelOperationName->setText(baseConfigWidget->getOperationName());
    QWidget *configWidget = baseConfigWidget->getConfigWidget();
    ui->scrollArea->setWidget(configWidget);
}

void MainWindow::GetSourceCaptureImage()
{
    cv::Mat capturedImg = captureInputSource->resizedImg;
    if(isSourceFlipped)
    {
        cv::flip(capturedImg, capturedImg, 1);
    }

    RefreshInputImage(capturedImg);
    RefreshOutputImage(capturedImg);
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

MainWindow::~MainWindow()
{
    delete ui;
}
