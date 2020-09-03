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

    // Register custom data type to make them queueable
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>>>
            ("QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>>");

    initUI();
    connectSignals();

    // FIXME: Check FIXME in HybridSlider cpp source
    //    HybridSlider* hybrid = new HybridSlider();
    //    hybrid->show();

    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(client);
    client->setLayout(loGrid);

    pageWidget->setLayout(new QVBoxLayout);
    pageWidget->layout()->addWidget(scrollArea);
    tabPage->addTab(pageWidget, "Page");
    tabPage->show();

    //    QString title = QString("Page %1").arg(1);
    //    QTabWidget *tab = new QTabWidget();

    //    tab->addTab(tabPage, title);
    //    client->show();
}

void MainWindow::initUI()
{
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

    ui->buttonStopRec->setDisabled(true);
    ui->buttonExportBrowse->setEnabled(true);

    errorDialog->setModal(true);

    sourceRadioButtonClicked();
    ioErrorMessage("");
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

void MainWindow::connectSignals()
{
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

    connect(ui->buttonExportBrowse, &QToolButton::released,
            this, [=]()
    {
        exportFolderPath =
                QFileDialog::getExistingDirectory(this);
        if(!exportFolderPath.isEmpty())
        {
            ui->buttonStopRec->setDisabled(true);
            ui->buttonExportBrowse->setEnabled(true);
        }
    });
    connect(ui->buttonStartRec, SIGNAL(released()),
            this, SLOT(startRecClicked()));
    connect(ui->buttonStopRec, SIGNAL(released()),
            this, SLOT(stopRecClicked()));
    connect(ui->buttonCapture, SIGNAL(released()),
            this, SLOT(captureClicked()));

    connect(ui->explodedViewCB, SIGNAL(stateChanged(int)),
            this, SLOT(showHideExplodedView(int)));
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

    connect(this, SIGNAL(updateExplodedViewSignal(QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>>)),
            this, SLOT(updateExplodedView(QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>>)));

    connect(this, SIGNAL(showErrorDialog(QString, QString)),
            this, SLOT(showOperationalError(QString, QString)));

    userMsgTimer->setSingleShot(true);
    connect(userMsgTimer, &QTimer::timeout,
            this, [=](){
        setUserMessage("", INFO);
    });

    ioMsgTimer->setSingleShot(true);
    connect(ioMsgTimer, &QTimer::timeout,
            this, [=](){
        ioErrorMessage("");
    });

    connect(this, &MainWindow::updateFPSLabel,
            this, [=](int fps){
        ui->labelInputFPS->setText(
                    QString(Strings::fps).arg(fps));
    });
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

    qDebug() << "baseConfigWidgetChain size = " << baseConfigWidgetChain.size();
}

void MainWindow::operationSelectedToDisplay(ParamAdjustWidget* paramAdjustWidget)
{
    for(int i = 0; i < testVBox->count(); i++)
    {
        QLayoutItem *itemParamAdjust = testVBox->itemAt(i);
        itemParamAdjust->widget()->hide();
    }

    paramAdjustWidget->show();

    // NOTE: Experimental implementation of Exploded View Feature
    cv::destroyAllWindows();
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

    connect(ui->labelOutput, SIGNAL(LBclicked(QPoint)),
            baseConfigWidgetChain.last(), SLOT(beginPointChanged(QPoint)));

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

    qDebug() << "Chain Menu vBox count before: " << chainMenuVBox->count();

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

    qDebug() << "Chain Menu vBox count after: " << chainMenuVBox->count();

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

    // NOTE: Experimental implementation of Exploded View Feature
    cv::destroyAllWindows();
}

void MainWindow::getSourceCaptureImage(cv::Mat originalImg)
{
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
        QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>> explodedViewList;
        originalImg.copyTo(outputImage);
        bool isChainSuccess = false;
        for(auto&& baseConfigWidget : baseConfigWidgetChain)
        {
            isChainSuccess = false;
            try
            {
                cv::Mat currentInput = outputImage.clone();
                outputImage = baseConfigWidget->getProcessedImage(outputImage);
                auto currentExplodedView = baseConfigWidget->getExplodedViewMats();
                currentExplodedView.insert("Input", currentInput);
                currentExplodedView.insert("Output", outputImage.clone());

                // NOTE: Experimental implementation of Exploded View Feature
                if((explodedViewState == 1
                    && baseConfigWidget->getChainMenuWidget()->getRadioButton()->isChecked())
                        || explodedViewState == 2)
                    explodedViewList.insert(baseConfigWidget->getUUID(),
                                            qMakePair(baseConfigWidget->getOperationName(), currentExplodedView));
                isChainSuccess = true;
            }
            catch(cv::Exception& e)
            {
                qCritical() << e.what();
                emit showErrorDialog("OpenCV Exception", e.what());
            }
            catch(std::exception& e)
            {
                qCritical() << e.what();
                emit showErrorDialog("Standard Exception", e.what());
            }
            catch(std::string &error)
            {
                qCritical() << QString::fromStdString(error);
                emit showErrorDialog("Unknown Exception",
                                     QString::fromStdString(error));
            }
            if(!isChainSuccess)
            {
                qCritical() << "Errored operation removed from Chain";

                originalImg.copyTo(outputImage);

                emit removeOperationWidgetSignal();
                break;
            }
        }

        emit refreshOutputImageSignal(outputImage);

        if(explodedViewState != 0)
            emit updateExplodedViewSignal(explodedViewList);

        qmutex.unlock();
    });

    // If Chain becomes empty, add NO_OPERATION to the chain
    if(testVBox->count() == 0) addOperation();
}

void MainWindow::showOperationalError(QString title, QString error)
{
    qCritical() << error;

    if(errorDialog->isVisible())
    {
        QString errorDetails = errorDialog->getDetails();
        errorDetails += error;
        errorDialog->setText(title, errorDetails);

        /*
         * Increement Continuous Error Count if error DIalog is already
         * showing and another error appears
         */
        continuousErrorCount++;
    }
    else if(!errorDialog->isVisible())
    {
        errorDialog->setText(title, error);
        errorDialog->show();
        continuousErrorCount = 0;
    }

    if(continuousErrorCount >= continuousErrorThreshold)
    {
        qCritical() << "Continous Error threshold crossed";
        // TODO: Show OpenCV Catalogue Hard Reset Button
    }

    /*
     * FIXME: Commented for DEMO,
     *  show in Alert Dialog instead of user message label
     */
    //    setUserMessage(error, ERROR);
}

void MainWindow::refreshInputImage(const cv::Mat img)
{
    try
    {
        cv::Mat inputImage;
        img.copyTo(inputImage);

        if(isRecording)
            writeToVideo(inputVideo, inputImage);

        // QT expects RGB Matrix instead of OpenCV's defalt BGR
        cvtColor(inputImage, inputImage, cv::COLOR_BGR2RGB);

        inputPixMap = QPixmap::fromImage(
                    QImage(
                        inputImage.data, inputImage.cols,
                        inputImage.rows, inputImage.step,
                        QImage::Format_RGB888));
        ui->labelInput->setPixmap(inputPixMap.scaled(ui->labelInput->width(),
                                                     ui->labelInput->height(),
                                                     Qt::KeepAspectRatio));
    }

    catch(cv::Exception& e)
    {
        qWarning() << e.what();
        setUserMessage("Error Occured while refreshing the input image label: "
                       + QString::fromStdString(e.what()), ERROR);
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

        if(isRecording)
            writeToVideo(outputVideo, outputImage);

        // QT expects RGB Matrix instead of OpenCV's defalt BGR
        cvtColor(outputImage, outputImage, cv::COLOR_BGR2RGB);

        outputPixMap = QPixmap::fromImage(
                    QImage(
                        outputImage.data, outputImage.cols,
                        outputImage.rows, outputImage.step,
                        QImage::Format_RGB888));
        ui->labelOutput->setPixmap(outputPixMap.scaled(ui->labelOutput->width(),
                                                       ui->labelOutput->height(),
                                                       Qt::KeepAspectRatio));
        updateOutputFPS();
    }
    catch(cv::Exception& e)
    {
        qWarning() << e.what();
        setUserMessage("Error Occured while refreshing the output image label: "
                       + QString::fromStdString(e.what()), ERROR);
    }
}

void MainWindow::updateOutputFPS()
{

    auto currentTime = QDateTime::currentMSecsSinceEpoch();
    if(prevOutputFPSShowTime == -1)
        prevOutputFPSShowTime = currentTime;
    if(prevOutputTime != -1)
    {
        auto timeDifference = currentTime - prevOutputTime;
        if(timeDifference == 0)
            return;

        double outputFps = 1000 / timeDifference;
        aggregateOutputFPS = qMakePair(
                    aggregateOutputFPS.first + 1,
                    aggregateOutputFPS.second + outputFps
                    );
        if(currentTime - prevOutputFPSShowTime >= 500)
        {
            prevOutputFPSShowTime = currentTime;
            ui->labelOutputFPS->setText(
                        QString(Strings::fps).arg(
                            Numeric::setPrecision(
                                aggregateOutputFPS.second
                                /aggregateOutputFPS.first,
                                2)
                            )
                        );
            aggregateOutputFPS = qMakePair(0, 0);
        }
    }
    prevOutputTime = currentTime;
}

void MainWindow::updateExplodedView(QMap<QUuid, QPair<QString, QMap<QString, cv::Mat>>> explodedViewList)
{
    for(auto& explodedView: explodedViewList)
    {
        QString operationName = explodedView.first;

        QMapIterator<QString, cv::Mat> i(explodedView.second);
        while (i.hasNext())
        {
            i.next();
            QString title = operationName + ": " + i.key();
            cv::imshow(title.toStdString(), i.value());
        }
    }
}

void MainWindow::showHideExplodedView(int state)
{
    explodedViewState = state;

    if(state == 0)
        cv::destroyAllWindows();

    qDebug() << "Exploded View CB State = " << state;
    if(baseConfigWidgetChain.empty())
        return;

    setUserMessage("Exploded View feature is still in development phase!", WARNING);

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

    ioErrorMessage("");
    if(ui->cameraRadioButton->isChecked())
    {
        ui->buttonBrowse->hide();
        ui->labelInputSource->setText("Set Camera Index");
        ui->textInputSource->setText("");
        ui->textInputSource->setPlaceholderText("Ex: 0");
    }
    else if(ui->fileRadioButton->isChecked())
    {
        ui->buttonBrowse->show();
        ui->labelInputSource->setText("Browse for Video or Image file");
        ui->textInputSource->setText("");
        ui->textInputSource->setPlaceholderText("File path...");
    }
    else if(ui->ipcamRadioButton->isChecked())
    {
        ui->buttonBrowse->hide();
        ui->labelInputSource->setText("Set Camera IP Address");
        ui->textInputSource->setText("");
        ui->textInputSource->setPlaceholderText("Ex: http://192.168.1.10:8080/video");
    }
}

void MainWindow::browseClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(filePath.length() > 0)
        ui->textInputSource->setText(filePath);
}

void MainWindow::startRecClicked()
{
    if(captureInputSource == nullptr || inputPixMap.isNull() || outputPixMap.isNull())
    {
        qWarning() << "No input Source selected to start recording";
        ioErrorMessage("Please select an input source!");
        return;
    }
    if(exportFolderPath.isEmpty())
    {
        qWarning() << "Export Folder not selected";
        ioErrorMessage("Please select a folder to export recording");
        return;
    }

    QString inputVideoFileName = "Input-" + QDateTime::currentDateTime()
            .toString(Qt::DateFormat::ISODateWithMs)
            .replace(":", "-")
            .replace(".", "-")
            + ".avi";

    inputVideo = cv::VideoWriter((exportFolderPath + "/" + inputVideoFileName).toStdString(),
                                 cv::VideoWriter::fourcc('M','J','P','G'),
                                 captureInputSource->getCurrentFPS(),
                                 cv::Size(inputPixMap.width(), inputPixMap.height()),
                                 true);

    QString outputVideoFileName = "Output-" + QDateTime::currentDateTime()
            .toString(Qt::DateFormat::ISODateWithMs)
            .replace(":", "-")
            .replace(".", "-")
            + ".avi";

    outputVideo = cv::VideoWriter((exportFolderPath + "/" + outputVideoFileName).toStdString(),
                                  cv::VideoWriter::fourcc('M','J','P','G'),
                                  captureInputSource->getCurrentFPS(),
                                  cv::Size(outputPixMap.width(), outputPixMap.height()),
                                  true);

    isRecording = true;

    ui->buttonStopRec->setEnabled(true);
    ui->buttonStartRec->setDisabled(true);
    ui->buttonExportBrowse->setDisabled(false);
}

void MainWindow::stopRecClicked()
{
    isRecording = false;

    try
    {
        inputVideo.release();
        outputVideo.release();
        setUserMessage("Recording saved to destination folder", INFO);
    }
    catch (cv::Exception e)
    {
        qCritical() << e.what();
        ioErrorMessage("Recording failed! Please try again");
    }

    ui->buttonStopRec->setDisabled(true);
    ui->buttonStartRec->setEnabled(true);
    ui->buttonExportBrowse->setEnabled(true);

    setUserMessage("", INFO);
}

void MainWindow::writeToVideo(cv::VideoWriter videoWriter, cv::Mat img)
{
    if(!videoWriter.isOpened() || img.total() == 0)
    {
        qCritical() << "Video Write failed!";
        return;
    }
    try
    {
        videoWriter.write(img);
        setUserMessage("Recording...", WARNING);
    }
    catch (cv::Exception e)
    {
        qCritical() << "Video writing failed. Aborting!";
        stopRecClicked();
        ioErrorMessage("Video Writing Failed! Please retry.");
    }
}

void MainWindow::captureClicked()
{
    if(inputPixMap.isNull() || outputPixMap.isNull())
    {
        qWarning() << "No input Source selected to start recording";
        ioErrorMessage("Please select an input source!");
        return;
    }
    if(exportFolderPath.isEmpty())
    {
        qWarning() << "Export Folder not selected";
        ioErrorMessage("Please select a folder to export captured images");
        return;
    }

    QString inputFilename = "Input-" + QDateTime::currentDateTime()
            .toString(Qt::DateFormat::ISODateWithMs)
            .replace(":", "-")
            .replace(".", "-")
            + ".png";
    QString outputFilename = "Output-" + QDateTime::currentDateTime()
            .toString(Qt::DateFormat::ISODateWithMs)
            .replace(":", "-")
            .replace(".", "-")
            + ".png";

    try
    {
        QFile ifile(exportFolderPath + "/" + inputFilename);
        QFile ofile(exportFolderPath + "/" + outputFilename);

        if(!(inputPixMap.save(&ifile) && outputPixMap.save(&ofile)))
        {
            qWarning() << "Image Exporting Failed";
            ioErrorMessage("Capturing failed! Please select a valid destination.");
        }
        else
        {
            qInfo() << "Image Exporting Success!";
            ioErrorMessage("Captures images, saved to destination folder");
        }
    }
    catch(QException e)
    {
        qCritical() << "Error: " << e.what();
        ioErrorMessage("Image exporting failed! Please try again.");
    }
}

void MainWindow::applySourceClicked()
{
    QString path = ui->textInputSource->text();
    qDebug() << "Source Selected, path = " << path;

    if(path.isEmpty())
    {
        qWarning() << "Input source path empty!";
        ioErrorMessage("Please enter input source path!");
        return;
    }
    ioErrorMessage("");

    int inputSourceType = CaptureInputSource::FILE;
    if(ui->fileRadioButton->isChecked()){
        inputSourceType = CaptureInputSource::FILE;
        QFileInfo check_file(path);
        if (!(check_file.exists() && check_file.isFile()))
        {
            qWarning() << "No file present on entered path";
            ioErrorMessage("Provided file path does not exist!");
            return;
        }
    }
    else if(ui->cameraRadioButton->isChecked())
    {
        inputSourceType = CaptureInputSource::HARDWARE_CAM;
        if (!QRegExp(RegExps::onlyDigits).exactMatch(path))
        {
            qWarning() << "Invalid camera index";
            ioErrorMessage("Please enter a valid camera index!");
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
        connect(captureInputSource, &CaptureInputSource::sourceCaptureError,
                this, [=](QString error)
        {
            emit showErrorDialog("Input Source Error", error);
        });
        connect(captureInputSource, &CaptureInputSource::updateFPS,
                this, [=](int fps)
        {
            emit updateFPSLabel(fps);
        });
    }

    emit captureInputSource->setInputSource(inputSourceType, path);
}

void MainWindow::outputLabelLBClicked(QPoint point)
{
    qDebug() << "Output label Mouse LB button click pos = " << point;
}

void MainWindow::toggleFlipSource(bool isChecked)
{
    isSourceFlipped = isChecked;
}

void MainWindow::ioErrorMessage(QString message)
{
    if(message.isEmpty())
    {
        ui->labelIOStatus->setText(""); ui->labelIOStatus->setStyleSheet("");
        return;
    }
    ui->labelIOStatus->setText(message);
    ui->labelIOStatus->setStyleSheet("QLabel { color : red; }");

    ioMsgTimer->start(5000);
}

void MainWindow::setUserMessage(QString message, MESSAGE_TYPE messageType)
{
    if(message.isEmpty())
    {
        ui->labelUserMessage->setText("");
        return;
    }

    if(messageType != INFO)
        ui->labelUserMessage->setStyleSheet(QString("QLabel { color : ")
                                            + (messageType == ERROR ? "red":
                                                                      "yellow")
                                            + "; }");
    else if(messageType == INFO)
        ui->labelUserMessage->setStyleSheet("");

    ui->labelUserMessage->setText(message);

    userMsgTimer->start(5000);
}

void MainWindow::switchThemeButtonClicked()
{
    if(qApp->styleSheet() == "")
    {
        qDebug() << "Switching to Dark Theme";

        isDarkModeOn = true;
        QFile f(":qdarkstyle/style.qss");

        if (!f.exists())
        {
            qCritical() << "Unable to set stylesheet, Dark Mode Theme File not found!";
            return;
        }

        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());

        ui->labelInput->setStyleSheet("#labelInput \n{\n border: 2px solid #54636D;\n background-color : #32414B; \n color : white; \n}");
        ui->labelOutput->setStyleSheet("#labelOutput \n{\n border: 2px solid #54636D;\n background-color : #32414B; \n color : white; \n}");

        for(auto& baseConfigWidget : baseConfigWidgetChain)
        {
            baseConfigWidget->changeWidgetsStyleSheet(true);
        }
    }
    else
    {
        qDebug() << "Switching to Light Theme";

        isDarkModeOn = false;
        qApp->setStyleSheet("");

        ui->labelInput->setStyleSheet("border: 1px solid black");
        ui->labelOutput->setStyleSheet("border: 1px solid black");

        for(auto& baseConfigWidget : baseConfigWidgetChain)
        {
            baseConfigWidget->changeWidgetsStyleSheet(false);
        }
    }

    ui->buttonStartRec->setStyleSheet(exportButtonsStyleSheet.arg(isDarkModeOn ? "play_dark": "play_light",
                                                                  isDarkModeOn ? "play_light": "play_dark",
                                                                  "play_disabled"));
    ui->buttonStopRec->setStyleSheet(exportButtonsStyleSheet.arg(isDarkModeOn ? "stop_dark": "stop_light",
                                                                 isDarkModeOn ? "stop_light": "stop_dark",
                                                                 "stop_disabled"));
    ui->buttonCapture->setStyleSheet(exportButtonsStyleSheet.arg(isDarkModeOn ? "capture_dark": "capture_light",
                                                                 isDarkModeOn ? "capture_light": "capture_dark",
                                                                 "capture_disabled"));
}

void MainWindow::waitForChainProcessing()
{
    // TODO: Check if user need to notify of the wait?
    if(chainProcessFuture.isRunning())
        chainProcessFuture.waitForFinished();
}


void MainWindow::showAboutDialog()
{
    qDebug() << "Opening About Dialog";
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

MainWindow::~MainWindow()
{
    fclose(fp);
    delete ui;
    qDebug() << "Application Closed!";
}
