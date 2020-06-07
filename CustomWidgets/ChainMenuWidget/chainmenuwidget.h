#ifndef CHAINMENUWIDGET_H
#define CHAINMENUWIDGET_H

#include <QWidget>
#include <QPair>

namespace Ui {
class ChainMenuWidget;
}

class ChainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChainMenuWidget(QWidget *parent = nullptr,
                             QList<QPair<int, QString>> chainMenuOpList =
            QList<QPair<int, QString>>() << QPair<int, QString>(0 ,""));

    void setAddButonEnabled(bool enabled);
    void setRemoveButtonEnabled(bool enabled);
    void setComboBoxEnabled(bool enabled);
    void setEnabled(bool enabled);

//private slots:
//    void operationChangedSlot(int); // OpCode

    ~ChainMenuWidget();

signals:
    void addOperationClicked();
    void removeOperationClicked();
//    void operationChangedSignal(int chainMenuOpListIndex); // or OpCode

private:
    Ui::ChainMenuWidget *ui;
};

#endif // CHAINMENUWIDGET_H
