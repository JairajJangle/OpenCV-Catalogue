#ifndef HYBRIDSLIDER_H
#define HYBRIDSLIDER_H

#include <QWidget>

namespace Ui {
class HybridSlider;
}

class HybridSlider : public QWidget
{
    Q_OBJECT

public:
    explicit HybridSlider(QWidget *parent = nullptr,
                          int initVal = 0,
                          int rangeMin = 0,
                          int rangeMax = 100);
    ~HybridSlider();

private slots:
    void showRangeBox();
    void applyValues();
    void valueChanged(int);

signals:
    void editApplyClicked();

private:
    Ui::HybridSlider *ui;

    enum MODE{
        EDIT, APPLIED, FORCE_VALUE
    };

    MODE currentMode = APPLIED;

    int initVal;
    int rangeMin;
    int rangeMax;
};

#endif // HYBRIDSLIDER_H
