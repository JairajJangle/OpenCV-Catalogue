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
    QPushButton* infoButton = new QPushButton();
    QPushButton* removeButton = new QPushButton();
    QParallelAnimationGroup* toggleAnimation = new QParallelAnimationGroup();
    QScrollArea* contentArea = new QScrollArea();
    int animationDuration{300};

    QString infoButtonStyleSheet = QString("QPushButton#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}"
                                           "QPushButton:pressed#infoButton"
                                           "{"
                                           "    background-color: transparent;"
                                           "    border-image: url(:/assets/info_sel.png);"
                                           "    background: none;"
                                           "    border: none;"
                                           "    background-repeat: none;"
                                           "}");

    QString removeButtonStyleSheet = QString("QPushButton#removeButton"
                                             "{"
                                             "  color: red;"
                                             "  font-weight: bold;"
                                             "}"
                                             "QPushButton:disabled#buttonRemove"
                                             "{"
                                             "  color: #787878;"
                                             "  font-weight: bold;"
                                             "  background-color: #ffffff;"
                                             "}");
};
