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
    void valueChanged(int);
    void valLineEditFocusChanged(bool);
    void valueChanged(const QString&);

signals:
    void editApplyClicked();

private:
    Ui::HybridSlider *ui;

    enum MODE{
        EDIT, APPLIED
    };

    MODE currentMode = APPLIED;
    MODE previousMode = EDIT;

    int initVal;
    int rangeMin;
    int rangeMax;

    void setRangeBoxVisibility(bool visibility);

    bool isLineEditFocused;
};

#endif // HYBRIDSLIDER_H
