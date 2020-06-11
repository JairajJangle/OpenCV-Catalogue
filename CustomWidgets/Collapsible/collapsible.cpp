#include <QPropertyAnimation>

#include "collapsible.h"

Collapsible::Collapsible(const int animationDuration,
                         QWidget *parent) : QFrame(parent), animationDuration(animationDuration)
{
    toggleButton->setText(Strings::noOperationSelected);
    toggleButton->setStyleSheet("QToolButton { border: none; }");
    toggleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toggleButton->setArrowType(Qt::ArrowType::RightArrow);
    toggleButton->setCheckable(true);
    toggleButton->setChecked(false);
    toggleButton->setMinimumHeight(50);

    infoButton->setFixedSize(25, 25);
    infoButton->setObjectName("infoButton");
    infoButton->setStyleSheet(infoButtonStyleSheet);
    infoButton->hide();

    removeButton->setMaximumSize(25, 25);
    removeButton->setObjectName("removeButton");
    removeButton->setText("—");
    removeButton->setStyleSheet(removeButtonStyleSheet);
    connect(removeButton, &QPushButton::released,
            this, [=]() {
        emit removeButtonClicked();
    });

    headerLine->setFrameShape(QFrame::HLine);
    headerLine->setFrameShadow(QFrame::Sunken);
    headerLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(headerLine);
    hBox->addWidget(infoButton);

    //    contentArea.setStyleSheet("QScrollArea { background-color: white; border: none; }");
    contentArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contentArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // start out collapsed
    contentArea->setMaximumHeight(0);
    contentArea->setMinimumHeight(0);
    // let the entire widget grow and shrink with its content
    toggleAnimation->addAnimation(new QPropertyAnimation(this, "minimumHeight"));
    toggleAnimation->addAnimation(new QPropertyAnimation(this, "maximumHeight"));
    toggleAnimation->addAnimation(new QPropertyAnimation(contentArea, "maximumHeight"));
    // don't waste space
    mainLayout->setVerticalSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    int row = 0;
    mainLayout->addWidget(toggleButton, row, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(infoButton, row, 1, 1, 1);
    mainLayout->addWidget(headerLine, row++, 2, 1, 1);
//    mainLayout->addWidget(removeButton, row++, 4, 1, 2);
    mainLayout->addWidget(contentArea, row, 0, 1, 8);
    setLayout(mainLayout);
    QObject::connect(toggleButton, &QToolButton::clicked, [this](const bool checked) {
        toggleButton->setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
        toggleAnimation->setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
        toggleAnimation->start();
    });

    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);
}

void Collapsible::setContentLayout(QWidget* contentLayout,
                                   const QString title,
                                   const QString infoLink)
{
    delete contentArea->layout();
    toggleButton->setText(title);
    contentArea->setWidget(contentLayout);

    const auto collapsedHeight = sizeHint().height() - contentArea->maximumHeight();
    auto contentHeight = contentLayout->sizeHint().height() + 10;

    for (int i = 0; i < toggleAnimation->animationCount() - 1; ++i) {
        QPropertyAnimation * CollapsibleAnimation =
                static_cast<QPropertyAnimation*>(toggleAnimation->animationAt(i));
        CollapsibleAnimation->setDuration(animationDuration);
        CollapsibleAnimation->setStartValue(collapsedHeight);
        CollapsibleAnimation->setEndValue(collapsedHeight + contentHeight);
    }
    QPropertyAnimation * contentAnimation =
            static_cast<QPropertyAnimation*>(toggleAnimation->
                                             animationAt(toggleAnimation->animationCount() - 1));
    contentAnimation->setDuration(animationDuration);
    contentAnimation->setStartValue(0);
    contentAnimation->setEndValue(contentHeight);

    if(infoLink != "")
    {
        infoButton->show();
        connect(infoButton, &QPushButton::released,
                this, [=]() {
            QDesktopServices::openUrl(QUrl(infoLink));
        });
    }
}
