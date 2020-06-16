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

    switchThemeButtonClicked();

    configChainMenuList();

    // FIXME: Check FIXME in HybridSlider cpp source
    //    HybridSlider* hybrid = new HybridSlider();
    //    hybrid->show();

    connect(ui->cameraRadioButton,SIGNAL(clicked()),this,SLOT(sourceRadioButtonClicked()));
    connect(ui->fileRadioButton,SIGNAL(clicked()),this,SLOT(sourceRadioButtonClicked()));
    connect(ui->buttonSelectSource,SIGNAL(released()),this,SLOT(sourceSelectClicked()));
    connect(ui->checkBoxMirror, SIGNAL(clicked(bool)), this, SLOT(toggleFlipSource(bool)));
    connect(ui->buttonBrowse,SIGNAL(released()),this,SLOT(browseClicked()));
    connect(ui->buttonExplodedView,SIGNAL(released()),this,SLOT(showHideExplodedView()));
    connect(ui->buttonSwitchTheme, SIGNAL(released()), this, SLOT(switchThemeButtonClicked()));

    connect(ui->actionAbout, &QAction::triggered, this,
            [=]() {
        showAboutDialog();
    });

    connect(ui->labelOutput, SIGNAL(LBclicked(int, int)), this, SLOT(outputLabelLBClicked(int, int)));

    connect(this, SIGNAL(removeOperationWidgetsSignal()),
            this, SLOT(removeOperationWidgets()));

    connect(this, SIGNAL(refreshOutputImageSignal(cv::Mat)), this, SLOT(refreshOutputImage(cv::Mat)));

    ui->scrollAreaParameterWidget->setWidgetResizable(true);

    addOperation(NONE);
}

void MainWindow::initUI(){
    this->setWindowTitle(Info::appName);
    this->setWindowIcon(QIcon(":/assets/app_logo.png"));

    ui->scrollAreaChainMenu->setWidget(wgtSub);
    vBoxSub->setAlignment(Qt::AlignTop);
    vBoxSub->setSpacing(0);

    testVBox->setAlignment(Qt::AlignTop);
    ui->scrollAreaParameterWidget->setWidget(wgtSubtest);

    QButtonGroup* group = new QButtonGroup();
    group->addButton(ui->cameraRadioButton);
    group->addButton(ui->fileRadioButton);

    sourceRadioButtonClicked();

    setUserMessage("Initializing Done", INFO);
}

void MainWindow::addOperation(OPCodes opCode)
{
    switch (opCode)
    {
    case NONE:
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
    case THRESHOLDING:
        baseConfigWidgetChain.append(new Thresholding());
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
    }

    currentSelectionIndex = baseConfigWidgetChain.size() - 1;

    addOperationWidget();

    qDebug() << "Current Selection Index = " << currentSelectionIndex;
}

void MainWindow::lastOperationChanged(OPCodes opCode)
{
    baseConfigWidgetChain.removeLast();
    removeOperationWidgets();
    addOperation(opCode);

    qDebug() << "Base Config size = " << baseConfigWidgetChain.size();
}

// FIXME: Test
void MainWindow::operationSelectedToDisplay(ParamAdjustWidget* paramAdjustWidget)
{
    qDebug() << "Operation Clicked";

    for(int i = 0; i < testVBox->count(); i++)
    {
        QLayoutItem *itemParamAdjust = testVBox->itemAt(i);
        itemParamAdjust->widget()->hide();
    }

    paramAdjustWidget->show();
}

void MainWindow::addOperationWidget()
{
    if(!baseConfigWidgetChain.empty())
    {
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
            baseConfigWidgetChain.removeLast();
            emit removeOperationWidgetsSignal();
        });

        connect(baseConfigWidgetChain.last(), SIGNAL(operationSelected(ParamAdjustWidget*)),
                this, SLOT(operationSelectedToDisplay(ParamAdjustWidget*)));

        vBoxSub->addWidget(baseConfigWidgetChain.last()->getChainMenuWidget());
        vBoxSub->update();

        refreshOperationWidgets();
    }
    else
        qDebug() << "baseConfigWidgetChain is empty";
}

void MainWindow::removeOperationWidgets()
{
    qDebug() << "VBox Count Before: " << vBoxSub->count();

    QLayoutItem *item = vBoxSub->itemAt(vBoxSub->count() - 1);
    item->widget()->hide();
    vBoxSub->removeWidget(item->widget());

    if(testVBox->count() != 0)
    {
        QLayoutItem *itemParamAdjust = testVBox->itemAt(testVBox->count() - 1);
        itemParamAdjust->widget()->hide();
        testVBox->removeWidget(itemParamAdjust->widget());
    }

    if(!baseConfigWidgetChain.empty())
        baseConfigWidgetChain.last()->
                getParamAdjustWidget()->show();

    qDebug() << "VBox Count After: " << vBoxSub->count();

    //            vBoxSub->takeAt(ui->stackedWidget->count() - 1)->widget()->close();
    //        ui->stackedWidget->removeWidget(
    //                    ui->stackedWidget->widget(ui->stackedWidget->count() - 1));

    vBoxSub->update();

    ui->scrollAreaChainMenu->update();

    refreshOperationWidgets();
}

void MainWindow::refreshOperationWidgets()
{
    if(!baseConfigWidgetChain.empty())
    {
        qDebug() << "Refresh Called";
        baseConfigWidgetChain.last()->setExplodedView(false);
        baseConfigWidgetChain.last()->getChainMenuWidget()->
                getRadioButton()->setChecked(true);
        baseConfigWidgetChain.last()->getChainMenuWidget()->
                setLineVisibility(false);

        if(vBoxSub->count() > 1)
        {
            static_cast<ChainMenuWidget*>(vBoxSub->itemAt(vBoxSub->count() - 2)->
                                          widget())->setLineVisibility(true);
            static_cast<ChainMenuWidget*>(vBoxSub->itemAt(vBoxSub->count() - 2)->
                                          widget())->setEnabled(false);
            static_cast<ChainMenuWidget*>(vBoxSub->itemAt(vBoxSub->count() - 1)->
                                          widget())->setEnabled(true);
        }
        else if(vBoxSub->count() == 1)
        {
            static_cast<ChainMenuWidget*>(vBoxSub->itemAt(vBoxSub->count() - 1)->
                                          widget())->setEnabled(true);
            static_cast<ChainMenuWidget*>(vBoxSub->itemAt(vBoxSub->count() - 1)->
                                          widget())->setRemoveButtonEnabled(false);
        }

        wgtSub->update();
        wgtSub->repaint();

        ui->scrollAreaChainMenu->widget()->adjustSize();
        ui->scrollAreaParameterWidget->widget()->adjustSize();
        qApp->processEvents();
        ui->scrollAreaChainMenu->verticalScrollBar()
                ->triggerAction(QAbstractSlider::SliderToMaximum);
        ui->scrollAreaParameterWidget->verticalScrollBar()
                ->triggerAction(QAbstractSlider::SliderToMaximum);
    }
}

void MainWindow::showAboutDialog()
{
    if(aboutDialog != nullptr)
    {
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

    refreshInputImage(capturedReziedImg);

    QtConcurrent::run([=]
    {
        cv::Mat outputImage;
        capturedOriginalImg.copyTo(outputImage);
        bool isChainSuccess = false;
        for(BaseConfigWidget* baseConfigWidget : baseConfigWidgetChain)
        {
            isChainSuccess = false;
            try{
                outputImage = baseConfigWidget->getProcessedImage(outputImage);
                isChainSuccess = true;
            }
            catch(cv::Exception& e)
            {
                qDebug() << e.what();
            }
            catch(std::exception& e)
            {
                qDebug() << e.what();
            }
            catch(std::string &error)
            {
                qDebug() << QString::fromStdString(error);
            }
            if(!isChainSuccess)
            {
                qDebug() << "Errored Operation removed from Chain";

                capturedOriginalImg.copyTo(outputImage);

                baseConfigWidgetChain.removeLast();
                emit removeOperationWidgetsSignal();
                break;
            }
        }

        emit refreshOutputImageSignal(outputImage);
    });
}

void MainWindow::GetSourceCaptureError(QString error)
{
    setUserMessage(error, ERROR);
}

void MainWindow::refreshInputImage(cv::Mat img)
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

void MainWindow::refreshOutputImage(const cv::Mat img)
{
    cv::Mat outputImage;
    img.copyTo(outputImage);
    try
    {
        if(outputImage.type() == CV_8UC1)
            cvtColor(outputImage, outputImage, cv::COLOR_GRAY2BGR);

        cvtColor(outputImage, outputImage, cv::COLOR_BGR2RGB);
        QPixmap OpenCV2QTOP = QPixmap::fromImage(
                    QImage(
                        outputImage.data, outputImage.cols,
                        outputImage.rows, outputImage.step,
                        QImage::Format_RGB888));

        ui->labelOutput->setPixmap(OpenCV2QTOP);
    }

    catch(cv::Exception& e)
    {
        captureInputSource->resizedImg =cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    }
}

void MainWindow::showHideExplodedView()
{
    if(!baseConfigWidgetChain.empty())
    {
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
    qDebug() << "Source Select Clicked!!";
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
        // Start capture thread after confirming input source
        captureInputSource = new CaptureInputSource(path.toStdString());
        captureInputSource->moveToThread(cam_thread);
        cam_thread->start();

        connect(captureInputSource, SIGNAL(SourceCaptured()), this, SLOT(GetSourceCaptureImage()));
        connect(captureInputSource, SIGNAL(SourceCaptureError(QString)), this, SLOT(GetSourceCaptureError(QString)));
    }
    else{
        qDebug() << "Cam Thread already running!!";
        captureInputSource->inputSource = path.toStdString();
        captureInputSource->relesaseCap();
    }
}

void MainWindow::outputLabelLBClicked(int x, int y)
{
    // FIXME: Mouse click received by unselected widget
    if(!baseConfigWidgetChain.empty())
        baseConfigWidgetChain.last()->begin =cv::Point(x, y);
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

void MainWindow::configChainMenuList()
{
    chainMenuOpList.append(QPair<OPCodes, QString>(NONE ,BaseConfigWidget().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(COLOR_SPACES ,ColorSpace().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(IMAGE_FLIP ,ImageFlip().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(COLOR_PICKER ,ColorPicker().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(THRESHOLDING ,Thresholding().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(INRANGE ,InRange().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(CANNY_EDGE ,CannyEdge().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(BLUR ,Blur().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(BKG_SUBTRACT ,BackgroundSubtraction().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(HOUGH_CIRCLES ,HoughCircles().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(HOUGH_LINES ,HoughLines().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(HISTOGRAM_CALCULATION ,HistogramCalculation().getOperationName()));
    chainMenuOpList.append(QPair<OPCodes, QString>(HARRIS_CORNER ,HarrisCornerDetector().getOperationName()));
}

void MainWindow::switchThemeButtonClicked()
{
    // TODO: To switch to light mode

    if(qApp->styleSheet() == "")
    {

        QFile f(":qdarkstyle/style.qss");

        if (!f.exists())
        {
            qDebug() << "Unable to set stylesheet, file not found\n";
        }
        else
        {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            qApp->setStyleSheet(ts.readAll());
            ui->labelInput->setStyleSheet("#labelInput \n{\n border: 2px solid #54636D;\n background-color : #32414B; \n color : white; \n}");
            ui->labelOutput->setStyleSheet("#labelOutput \n{\n border: 2px solid #54636D;\n background-color : #32414B; \n color : white; \n}");
        }
    }
    else
    {
        qApp->setStyleSheet("");
        ui->labelInput->setStyleSheet("border: 1px solid black");
        ui->labelOutput->setStyleSheet("border: 1px solid black");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
