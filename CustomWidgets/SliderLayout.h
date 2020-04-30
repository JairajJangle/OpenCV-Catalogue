#ifndef SLIDERLAYOUT_H
#define SLIDERLAYOUT_H

#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>

class SliderLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    QLabel* titleLabel  = new QLabel();
    QLabel* valueLabel  = new QLabel();

    explicit SliderLayout(QString title, int initialValue, int minValue = 0, int maxValue = 100, int fixedWidth = 160, int fixedHeight = 60, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags())
    {
        this->setSpacing(15);

        QSlider* slider = new QSlider();
        slider->setFixedSize(fixedWidth, fixedHeight);
        slider->setSingleStep(20);
        slider->setOrientation(Qt::Horizontal);
        slider->setRange(minValue, maxValue);
        slider->setValue(initialValue);

        titleLabel->setText(title);
        valueLabel->setText(QString::number(initialValue));
        valueLabel->setFixedSize(40, 20);

        this->addWidget(titleLabel);
        this->addWidget(slider);
        this->addWidget(valueLabel);

        connect(slider, SIGNAL(valueChanged(int)),this,
                SLOT(valueChanged(int)));
        connect(slider, &QSlider::valueChanged,
                [=]() {
            emit sliderValueChanged(slider->value());
        });
    }
    ~SliderLayout()
    {

    }

signals:
    void sliderValueChanged(int);

private slots:
    void valueChanged(int value){
        valueLabel->setText(QString::number(value));
    }
};

#endif // SLIDERLAYOUT_H
