#ifndef APPLYRESETBUTTONLAYOUT_H
#define APPLYRESETBUTTONLAYOUT_H

#include <QHBoxLayout>
#include <QPushButton>

class ApplyResetButtonLayout : public QHBoxLayout
{
    Q_OBJECT

    QPushButton* applyButton = new QPushButton("Apply");
    QPushButton* resetButton = new QPushButton("Reset");

public:
    explicit ApplyResetButtonLayout(bool resetVisible = true,
                                    bool applyVisible = true,
                                    QWidget* parent = Q_NULLPTR,
                                    Qt::WindowFlags f = Qt::WindowFlags()){
        this->setAlignment(Qt::AlignHCenter);
        this->addWidget(applyButton);
        this->addWidget(resetButton);

        connect(applyButton, SIGNAL(released()),
                this, SLOT(applyClicked()));
        connect(resetButton, SIGNAL(released()),
                this, SLOT(resetClicked()));
    }

signals:
    void applyClicked();
    void resetClicked();
};

#endif // APPLYRESETBUTTONLAYOUT_H
