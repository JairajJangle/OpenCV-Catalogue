#ifndef CHAINMENUWIDGET_H
#define CHAINMENUWIDGET_H

#include <QWidget>

namespace Ui {
class ChainMenuWidget;
}

class ChainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChainMenuWidget(QWidget *parent = nullptr);
    ~ChainMenuWidget();

private:
    Ui::ChainMenuWidget *ui;
};

#endif // CHAINMENUWIDGET_H
