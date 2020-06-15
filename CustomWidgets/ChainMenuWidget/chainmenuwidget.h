#ifndef CHAINMENUWIDGET_H
#define CHAINMENUWIDGET_H

#include <QWidget>
#include <QPair>
#include <QRadioButton>

#include "Utils/utils.h"

namespace Ui {
class ChainMenuWidget;
}

class ChainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChainMenuWidget(QWidget *parent = nullptr);

    void setAddButonEnabled(bool enabled);
    void setRemoveButtonEnabled(bool enabled);
    void setComboBoxEnabled(bool enabled);
    void setEnabled(bool enabled);
    void setCurrentOperation(QString operationName);
    void setLineVisibility(bool visible);
    QRadioButton* getRadioButton();

    ~ChainMenuWidget();

signals:
    void addOperationClicked();
    void removeOperationClicked();
    void operationChanged(int index);
    void radioButtonChecked();

private:
    Ui::ChainMenuWidget *ui;
};

#endif // CHAINMENUWIDGET_H
