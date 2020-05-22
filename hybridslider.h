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
    explicit HybridSlider(QWidget *parent = nullptr);
    ~HybridSlider();

private slots:
    void showRangeBox();

private:
    Ui::HybridSlider *ui;
};

#endif // HYBRIDSLIDER_H
