#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

#include "Utils/constants.h"

class Collapsible : public QFrame {
    Q_OBJECT

public:
    explicit Collapsible(const int animationDuration = 300,
                         QWidget *parent = 0);
    void setContentLayout(QWidget* contentLayout,
                          const QString title,
                          const QString infoLink);
    void setInfoButtonVisibility(bool visible);

signals:
    void removeButtonClicked();
    void infoButtonClicled();

private:
    QGridLayout* mainLayout = new QGridLayout();
    QToolButton* toggleButton = new QToolButton();
    QFrame* headerLine = new QFrame();
    QToolButton* infoButton = new QToolButton();
    QToolButton* removeButton = new QToolButton();
    QParallelAnimationGroup* toggleAnimation = new QParallelAnimationGroup();
    QScrollArea* contentArea = new QScrollArea();
    int animationDuration{300};

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
