#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>
#include <QPushButton>

class Collapsible : public QFrame {
    Q_OBJECT
private:
    QGridLayout mainLayout;
    QToolButton toggleButton;
    QFrame headerLine;
    QPushButton infoButton;
    QPushButton removeButton;
    QParallelAnimationGroup toggleAnimation;
    QScrollArea contentArea;
    int animationDuration{300};
public:
    explicit Collapsible(const QString & title = "", const int animationDuration = 300, QWidget *parent = 0);
    void setContentLayout(QWidget & contentLayout);
};
