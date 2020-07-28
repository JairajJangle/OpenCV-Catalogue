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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Register cv::Mat type to make it queueable
    qRegisterMetaType<cv::Mat>("cv::Mat");

    initUI();

    // FIXME: Check FIXME in HybridSlider cpp source
    //    HybridSlider* hybrid = new HybridSlider();
    //    hybrid->show();

    // Connect MainWindow UI signals here
    connect(ui->cameraRadioButton,SIGNAL(clicked()),
            this,SLOT(sourceRadioButtonClicked()));
    connect(ui->fileRadioButton,SIGNAL(clicked()),
            this,SLOT(sourceRadioButtonClicked()));
    connect(ui->ipcamRadioButton,SIGNAL(clicked()),
            this,SLOT(sourceRadioButtonClicked()));

    connect(ui->buttonSelectSource,SIGNAL(released()),
            this,SLOT(applySourceClicked()));
    connect(ui->checkBoxMirror, SIGNAL(clicked(bool)),
            this, SLOT(toggleFlipSource(bool)));
    connect(ui->buttonBrowse,SIGNAL(released()),
            this,SLOT(browseClicked()));
    connect(ui->buttonExplodedView,SIGNAL(released()),
            this,SLOT(showHideExplodedView()));
    connect(ui->buttonSwitchTheme, SIGNAL(released()),
            this, SLOT(switchThemeButtonClicked()));

    connect(ui->actionAbout, &QAction::triggered, this,
            [=]() {
        showAboutDialog();
    });

    connect(ui->labelOutput, SIGNAL(LBclicked(QPoint)),
            this, SLOT(outputLabelLBClicked(QPoint)));

    connect(this, SIGNAL(removeOperationWidgetSignal()),
            this, SLOT(removeOperationWidget()));

    connect(this, SIGNAL(refreshOutputImageSignal(cv::Mat)),
            this, SLOT(refreshOutputImage(cv::Mat)));
}

void MainWindow::initUI(){
    this->setWindowTitle(Info::appName);
    this->setWindowIcon(QIcon(":/assets/app_logo.png"));

    ui->scrollAreaChainMenu->setWidget(chainMenuSubWgt);
    chainMenuVBox->setAlignment(Qt::AlignTop);
    chainMenuVBox->setSpacing(0);

    testVBox->setAlignment(Qt::AlignTop);
    ui->scrollAreaParameterWidget->setWidget(wgtSubtest);
    ui->scrollAreaParameterWidget->setWidgetResizable(true);

    QButtonGroup* group = new QButtonGroup();
    group->addButton(ui->cameraRadioButton);
    group->addButton(ui->fileRadioButton);
    group->addButton(ui->ipcamRadioButton);

    sourceRadioButtonClicked();
    switchThemeButtonClicked();

    chainMenuInitDone = false;
    for (int opCode = 0; opCode != OPCodes::NONE; ++opCode) {
        addOperation((OPCodes)opCode);
    }
    qDebug() <<  "All OpenCV Operation Widgets Initialized";
    chainMenuInitDone = true;
    addOperation(NONE);

    setUserMessage("Initializing Done", INFO);
}

void MainWindow::addOperation(OPCodes opCode)
{
    switch (opCode)
    {
    case NO_OPERATION:
        baseConfigWidgetChain.append(new BaseConfigWidget());
        break;
    case COLOR_SPACES:
        baseConfigWidgetChain.append(new ColorSpace());
        break;
    case IMAGE_FLIP:
        baseConfigWidgetChain.append(new ImageFlip());
        break;
    case COLOR_PICKER:
        baseConfigWidgetChain.append(new ColorPicker());
        break;
    case CANNY_EDGE:
        baseConfigWidgetChain.append(new CannyEdge());
        break;
    case INRANGE:
        baseConfigWidgetChain.append(new InRange());
        break;
    case BLUR:
        baseConfigWidgetChain.append(new Blur());
        break;
    case BKG_SUBTRACT:
        baseConfigWidgetChain.append(new BackgroundSubtraction());
        break;
    case HOUGH_CIRCLES:
        baseConfigWidgetChain.append(new HoughCircles());
        break;
    case HOUGH_LINES:
        baseConfigWidgetChain.append(new HoughLines());
        break;
    case HISTOGRAM_CALCULATION:
        baseConfigWidgetChain.append(new HistogramCalculation());
        break;
    case HARRIS_CORNER:
        baseConfigWidgetChain.append(new HarrisCornerDetector());
        break;
    case NONE:
        baseConfigWidgetChain.append(new BaseConfigWidget());
        break;
    case ERODE:
        baseConfigWidgetChain.append(new ErodeDilate(ErodeDilate::ERODE));
        break;
    case DILATE:
        baseConfigWidgetChain.append(new ErodeDilate(ErodeDilate::DILATE));
        break;
    case BITWISE_OPS:
        baseConfigWidgetChain.append(new BitWise());
        break;
    case CONTOURS:
        baseConfigWidgetChain.append(new Contours());
        break;

        /*
         * Append other OpenCV Operation Base Config Widgets
         * in corresponding case blocks above this line
         *
         * To add the case enumns, see MainWindow::OPCodes enum defined in mainwindow.h
         */

    default:
        baseConfigWidgetChain.append(new BaseConfigWidget());
    }

    if(chainMenuInitDone)
        return addOperationWidget();

    chainMenuOpMap.insert(opCode ,baseConfigWidgetChain.last()->getOperationName());

    baseConfigWidgetChain.last()->deleteLater();
    baseConfigWidgetChain.removeLast();
}

void MainWindow::lastOperationChanged(OPCodes opCode)
{
    emit removeOperationWidgetSignal();
    addOperation(opCode);

    qDebug() << "Base Config size = " << baseConfigWidgetChain.size();
}

void MainWindow::operationSelectedToDisplay(ParamAdjustWidget* paramAdjustWidget)
{
    qDebug() << "Operation radio button clicked: ";

    for(int i = 0; i < testVBox->count(); i++)
    {
        QLayoutItem *itemParamAdjust = testVBox->itemAt(i);
        itemParamAdjust->widget()->hide();
    }

    paramAdjustWidget->show();
}

void MainWindow::addOperationWidget()
{
    waitForChainProcessing();

    if(baseConfigWidgetChain.empty())
    {
        qDebug() << "baseConfigWidgetChain is empty";
        return;
    }

    qDebug() << "Chain size = " << baseConfigWidgetChain.size();

    if(testVBox->count() != 0)
    {
        QLayoutItem *itemParamAdjust = testVBox->itemAt(testVBox->count() - 1);
        itemParamAdjust->widget()->hide();
    }
    chainMenuRadioButtonsGroup->addButton(baseConfigWidgetChain.last()->
                                          getChainMenuWidget()->getRadioButton());

    testVBox->addWidget(baseConfigWidgetChain.last()->
                        getParamAdjustWidget());
    baseConfigWidgetChain.last()->getParamAdjustWidget()->show();

    connect(baseConfigWidgetChain.last()->getChainMenuWidget(),
            &ChainMenuWidget::addOperationClicked,
            this,
            [=](){
        addOperation(NONE);
    });

    connect(baseConfigWidgetChain.last()->getChainMenuWidget(),
            qOverload<int>(&ChainMenuWidget::operationChanged),
            this,
            [=](int index){
        lastOperationChanged((OPCodes)index);
    });

    connect(baseConfigWidgetChain.last()->getChainMenuWidget(),
            &ChainMenuWidget::removeOperationClicked,
            this,
            [=](){
        emit removeOperationWidgetSignal();
    });

    connect(baseConfigWidgetChain.last(), SIGNAL(operationSelected(ParamAdjustWidget*)),
            this, SLOT(operationSelectedToDisplay(ParamAdjustWidget*)));

    chainMenuVBox->addWidget(baseConfigWidgetChain.last()->getChainMenuWidget());
    chainMenuVBox->update();

    refreshOperationWidgets();
}

void MainWindow::removeOperationWidget()
{
    waitForChainProcessing();

    baseConfigWidgetChain.last()->deleteLater();
    baseConfigWidgetChain.removeLast();

    qDebug() << "VBox Count Before: " << chainMenuVBox->count();

    QLayoutItem *item = chainMenuVBox->itemAt(chainMenuVBox->count() - 1);
    item->widget()->hide();
    chainMenuVBox->removeWidget(item->widget());

    if(testVBox->count() != 0)
    {
        QLayoutItem *itemParamAdjust = testVBox->itemAt(testVBox->count() - 1);
        itemParamAdjust->widget()->hide();
        testVBox->removeWidget(itemParamAdjust->widget());
    }

    if(!baseConfigWidgetChain.empty())
        baseConfigWidgetChain.last()->
                getParamAdjustWidget()->show();

    qDebug() << "VBox Count After: " << chainMenuVBox->count();

    chainMenuVBox->update();
    ui->scrollAreaChainMenu->update();

    refreshOperationWidgets();
}

void MainWindow::refreshOperationWidgets()
{
    if(baseConfigWidgetChain.empty())
        return;

    qDebug() << "called";
    baseConfigWidgetChain.last()->setExplodedView(false);
    baseConfigWidgetChain.last()->getChainMenuWidget()->
            getRadioButton()->setChecked(true);
    baseConfigWidgetChain.last()->getChainMenuWidget()->
            setLineVisibility(false);

    if(chainMenuVBox->count() > 1)
    {
        dynamic_cast<ChainMenuWidget*>(chainMenuVBox->itemAt(chainMenuVBox->count() - 2)->
                                       widget())->setLineVisibility(true);
        dynamic_cast<ChainMenuWidget*>(chainMenuVBox->itemAt(chainMenuVBox->count() - 2)->
                                       widget())->setEnabled(false);
        dynamic_cast<ChainMenuWidget*>(chainMenuVBox->itemAt(chainMenuVBox->count() - 1)->
                                       widget())->setEnabled(true);
    }
    else if(chainMenuVBox->count() == 1)
    {
        dynamic_cast<ChainMenuWidget*>(chainMenuVBox->itemAt(chainMenuVBox->count() - 1)->
                                       widget())->setEnabled(true);
        dynamic_cast<ChainMenuWidget*>(chainMenuVBox->itemAt(chainMenuVBox->count() - 1)->
                                       widget())->setRemoveButtonEnabled(false);
    }

    chainMenuSubWgt->update();
    chainMenuSubWgt->repaint();

    ui->scrollAreaChainMenu->widget()->adjustSize();
    ui->scrollAreaParameterWidget->widget()->adjustSize();
    qApp->processEvents();
    ui->scrollAreaChainMenu->verticalScrollBar()
            ->triggerAction(QAbstractSlider::SliderToMaximum);
    ui->scrollAreaParameterWidget->verticalScrollBar()
            ->triggerAction(QAbstractSlider::SliderToMaximum);
}

void MainWindow::showAboutDialog()
{
    if(aboutDialog == nullptr)
    {
        aboutDialog = new AboutDialog(this);
        return showAboutDialog();
    }

    if(!aboutDialog->isVisible())
    {
        // Set About Dialog Window Position and Always on Top
        QPoint mainWindowCenter = WidgetUtils::getWidgetCenter(this);
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

void MainWindow::getSourceCaptureImage(cv::Mat originalImg)
{
    //    cv::Mat capturedReziedImg = captureInputSource->resizedImg;
    //    cv::Mat capturedOriginalImg = captureInputSource->img;

    if(cv::Size(originalImg.rows , originalImg.rows).empty())
    {
        qCritical() << "Invalid input image";
        return;
    }

    if(isSourceFlipped)
    {
        cv::flip(originalImg, originalImg, 1);
    }

    refreshInputImage(originalImg);

    if(chainProcessFuture.isRunning())
        return;

    chainProcessFuture = QtConcurrent::run([=]
    {
        qmutex.lock();
        cv::Mat outputImage;
        originalImg.copyTo(outputImage);
        bool isChainSuccess = false;
        for(auto&& baseConfigWidget : baseConfigWidgetChain)
        {
            isChainSuccess = false;
            try{
                // FIXME: Segmentation fault for intensive operations
                // FIXME: Use Signal Slot System to get the output Image instead of return
                outputImage = baseConfigWidget->getProcessedImage(outputImage);
                isChainSuccess = true;
            }
            catch(cv::Exception& e)
            {
                qWarning() << e.what();
            }
            catch(std::exception& e)
            {
                qWarning() << e.what();
            }
            catch(std::string &error)
            {
                qWarning() << QString::fromStdString(error);
            }
            if(!isChainSuccess)
            {
                qWarning() << "Errored Operation removed from Chain";

                originalImg.copyTo(outputImage);

                emit removeOperationWidgetSignal();
                break;
            }
        }

        emit refreshOutputImageSignal(outputImage);
        qmutex.unlock();
    });

    // If Chain becomes empty, add NO_OPERATION to the chain
    if(testVBox->count() == 0) addOperation();
}

void MainWindow::getSourceCaptureError(QString error)
{
    qCritical() << error;
    // FIXME: Commented for DEMO
    //    setUserMessage(error, ERROR);
}

void MainWindow::refreshInputImage(cv::Mat img)
{
    try
    {
        cv::Mat inputImage;
        // QT expects RGB Matrix instead of OpenCV's defalt BGR
        cvtColor(img, inputImage, cv::COLOR_BGR2RGB);

        cv::Mat scaledInputImage = fitToLargestDimen(inputImage, cv::Size(320, 240));
        QPixmap OpenCV2QTOP = QPixmap::fromImage(
                    QImage(
                        scaledInputImage.data, scaledInputImage.cols,
                        scaledInputImage.rows, scaledInputImage.step,
                        QImage::Format_RGB888));
        ui->labelInput->setPixmap(OpenCV2QTOP);
    }

    catch(cv::Exception& e)
    {
        qWarning() << e.what();
        // TODO
        //        captureInputSource->resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    }
}

void MainWindow::refreshOutputImage(const cv::Mat img)
{
    cv::Mat outputImage;
    img.copyTo(outputImage);

    try
    {
        /*
         * Output matrix should have three channels
         * If channel count is 1 then convert the image to 3 channeled matrix
         */
        if(outputImage.type() == CV_8UC1)
            cvtColor(outputImage, outputImage, cv::COLOR_GRAY2BGR);

        // QT expects RGB Matrix instead of OpenCV's defalt BGR
        cvtColor(outputImage, outputImage, cv::COLOR_BGR2RGB);

        cv::Mat scaledOutputImage = fitToLargestDimen(outputImage, cv::Size(640, 480));
        QPixmap OpenCV2QTOP = QPixmap::fromImage(
                    QImage(
                        scaledOutputImage.data, scaledOutputImage.cols,
                        scaledOutputImage.rows, scaledOutputImage.step,
                        QImage::Format_RGB888));
        ui->labelOutput->setPixmap(OpenCV2QTOP);
    }

    catch(cv::Exception& e)
    {
        // TODO
        //        captureInputSource->resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    }
}

cv::Mat MainWindow::fitToLargestDimen(cv::Mat input, cv::Size fitToSize)
{
    double w = -1, h = -1;

    if(input.cols >= input.rows)
    {
        w = fitToSize.width;
        h = (w / input.cols) * input.rows;
        if(h > fitToSize.height) h = fitToSize.height;
    }
    else if(input.rows > input.cols)
    {
        h = fitToSize.height;
        w = (h / input.rows) * input.cols;
        if(w > fitToSize.width) w = fitToSize.width;
    }
    fitToSize = cv::Size(w, h);

    cv::Mat scaledOutputImage;
    cv::resize(input, scaledOutputImage, fitToSize);

    return scaledOutputImage;
}

void MainWindow::showHideExplodedView()
{
    if(baseConfigWidgetChain.empty())
        return;

    if(baseConfigWidgetChain.last()->isExplodedViewEnabled())
    {
        if(baseConfigWidgetChain.last()->setExplodedView(true))
        {
            // TODO: Change Icon to minimize
        }
    }
    else
    {
        baseConfigWidgetChain.last()->setExplodedView(false);
        // TODO: Change Icon to exploded
    }
}

void MainWindow::sourceRadioButtonClicked(){
    if(ui->cameraRadioButton->isChecked())
    {
        ui->buttonBrowse->hide();
        ui->labelInputSource->setText("Set Camera Index");
        ui->textInputSource->setPlainText("");
        ui->textInputSource->setPlaceholderText("0");
    }
    else if(ui->fileRadioButton->isChecked())
    {
        ui->buttonBrowse->show();
        ui->labelInputSource->setText("Browse for Video or Image file");
        ui->textInputSource->setPlainText("");
        ui->textInputSource->setPlaceholderText("File path...");
    }
    else if(ui->ipcamRadioButton->isChecked())
    {
        ui->buttonBrowse->hide();
        ui->labelInputSource->setText("Set Camera IP Address");
        ui->textInputSource->setPlainText("");
        ui->textInputSource->setPlaceholderText("http://192.168.1.10:8080/video");
    }
}

void MainWindow::browseClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(filePath.length() > 0)
        ui->textInputSource->setPlainText(filePath);
}

void MainWindow::applySourceClicked()
{
    QString path = ui->textInputSource->toPlainText();
    qDebug() << "Source Selected: " << path;
    int inputSourceType = CaptureInputSource::FILE;
    if(ui->fileRadioButton->isChecked()){
        inputSourceType = CaptureInputSource::FILE;
        QFileInfo check_file(path);
        if (!(check_file.exists() && check_file.isFile()))
        {
            qWarning() << " Provided file does not exist";
            return;
        }
    }
    else if(ui->cameraRadioButton->isChecked())
    {
        inputSourceType = CaptureInputSource::HARDWARE_CAM;
        if (path == "")
        {
            qWarning() << "Camera Number not provided";
            return;
        }
    }
    else if(ui->ipcamRadioButton->isChecked())
    {
        inputSourceType = CaptureInputSource::NETWORK_STREAM;
        if (path == "")
        {
            qWarning() << "No IP address entered";
            return;
        }
    }

    if(captureInputSource == nullptr){
        captureInputSource = new CaptureInputSource();

        connect(captureInputSource, SIGNAL(sourceCaptured(cv::Mat)),
                this, SLOT(getSourceCaptureImage(cv::Mat)));
        connect(captureInputSource, SIGNAL(sourceCaptureError(QString)),
                this, SLOT(getSourceCaptureError(QString)));
    }

    emit captureInputSource->setInputSource(path, inputSourceType);
}

void MainWindow::outputLabelLBClicked(QPoint point)
{
    // FIXME: Mouse click received by unselected widget
    if(!baseConfigWidgetChain.empty())
        baseConfigWidgetChain.last()->begin = cv::Point(point.x(), point.y());
}

void MainWindow::toggleFlipSource(bool isChecked)
{
    isSourceFlipped = isChecked;
}

void MainWindow::setUserMessage(QString message, MESSAGE_TYPE messageType)
{
    QPalette sample_palette;

    messageType == ERROR ?
                sample_palette.setColor(
                    QPalette::WindowText, Qt::red):
                messageType == WARNING ?
                    sample_palette.setColor(QPalette::WindowText, Qt::yellow):
                    sample_palette.setColor(QPalette::WindowText, Qt::black);

    ui->labelUserMessage->setAutoFillBackground(true);
    ui->labelUserMessage->setPalette(sample_palette);
    ui->labelUserMessage->setText(message);
}

void MainWindow::switchThemeButtonClicked()
{
    // TODO: To switch to light mode

    if(qApp->styleSheet() == "")
    {
        isDarkModeOn = true;
        QFile f(":qdarkstyle/style.qss");

        if (!f.exists())
        {
            qCritical() << "Unable to set stylesheet, Dark Mode Theme File not found";
        }
        else
        {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            qApp->setStyleSheet(ts.readAll());
            ui->labelInput->setStyleSheet("#labelInput \n{\n border: 2px solid #54636D;\n background-color : #32414B; \n color : white; \n}");
            ui->labelOutput->setStyleSheet("#labelOutput \n{\n border: 2px solid #54636D;\n background-color : #32414B; \n color : white; \n}");
        }

        for(auto& baseConfigWidget : baseConfigWidgetChain)
        {
            baseConfigWidget->changeWidgetsStyleSheet(true);
        }
    }
    else
    {
        isDarkModeOn = false;
        qApp->setStyleSheet("");
        ui->labelInput->setStyleSheet("border: 1px solid black");
        ui->labelOutput->setStyleSheet("border: 1px solid black");

        for(auto& baseConfigWidget : baseConfigWidgetChain)
        {
            baseConfigWidget->changeWidgetsStyleSheet(false);
        }
    }
}

void MainWindow::waitForChainProcessing()
{
    // TODO: Check if user need to notify of the wait?
    if(chainProcessFuture.isRunning())
        chainProcessFuture.waitForFinished();
}

MainWindow::~MainWindow()
{
    delete ui;
}
