#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

#include "Utils/constants.h"

class Collapsible : public QFrame {
    Q_OBJECT

public:
    explicit Collapsible(QWidget *parent = 0);
    void setContentLayout(QWidget* contentLayout,
                          const QString title,
                          const QString infoLink);
    void setInfoButtonVisibility(bool visible);

signals:
    void removeButtonClicked();
    void infoButtonClicled();

private:
    QGridLayout* mainLayout = new QGridLayout();
    QLabel* toggleButton = new QLabel();
    QFrame* headerLine = new QFrame();
    QFrame* headerLine2 = new QFrame();
    QToolButton* infoButton = new QToolButton();
    int row = 0;

    QString infoButtonStyleSheet = QString("QToolButton#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}"
                                           "QToolButton:pressed#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info_sel.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}");

    QString removeButtonStyleSheet = QString("QToolButton#removeButton"
                                             "{"
                                             "  color: red;"
                                             "  font-weight: bold;"
                                             "}"
                                             "QToolButton:disabled#buttonRemove"
                                             "{"
                                             "  color: #787878;"
                                             "  font-weight: bold;"
                                             "  background-color: #ffffff;"
                                             "}");
};
