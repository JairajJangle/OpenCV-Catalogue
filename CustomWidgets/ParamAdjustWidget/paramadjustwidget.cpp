#include <QPropertyAnimation>

#include "paramadjustwidget.h"
#include <QDebug>

ParamAdjustWidget::ParamAdjustWidget(QWidget *parent) : QFrame(parent)
{
    toggleButton->setText(Strings::noOperationSelected);
    toggleButton->setStyleSheet("QToolButton { border: none; }");
    toggleButton->setMinimumHeight(50);

    this->setStyleSheet("QFrame { border: none; }");
    infoButton->setFixedSize(25, 25);
    infoButton->setObjectName("infoButton");
    infoButton->setStyleSheet(infoButtonStyleSheet);
    infoButton->hide();

    headerLine2->setFrameShape(QFrame::HLine);
    headerLine2->setFrameShadow(QFrame::Sunken);
    headerLine2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    QHBoxLayout* titleHBox = new QHBoxLayout();
    titleHBox->addWidget(toggleButton);
    titleHBox->addStretch();
    titleHBox->addWidget(infoButton);

    mainLayout->setVerticalSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(titleHBox, row, 0, 1, 8);
    mainLayout->addWidget(headerLine2, ++row, 0, 1, 8);
    setLayout(mainLayout);

    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);
}

void ParamAdjustWidget::setContentLayout(QWidget* contentLayout,
                                         const QString title,
                                         const QString infoLink)
{
    toggleButton->setText(title);

    mainLayout->addWidget(contentLayout, 3, 0, 1, 8, Qt::AlignTop);
    setLayout(mainLayout);
    if(infoLink != "")
    {
        infoButton->show();
        connect(infoButton, &QToolButton::released,
                this, [=]() {
            QDesktopServices::openUrl(QUrl(infoLink));
        });
    }

    //    toggleAnimation->start();
}
