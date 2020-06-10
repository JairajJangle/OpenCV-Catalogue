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
    QGridLayout* mainLayout = new QGridLayout();
    QToolButton* toggleButton = new QToolButton();
    QFrame* headerLine = new QFrame();
    QPushButton* infoButton = new QPushButton();
    QPushButton* removeButton = new QPushButton();
    QParallelAnimationGroup* toggleAnimation = new QParallelAnimationGroup();
    QScrollArea* contentArea = new QScrollArea();
    int animationDuration{300};
public:
    explicit Collapsible(const int animationDuration = 300,
                         QWidget *parent = 0);
    void setContentLayout(QWidget* contentLayout,
                          const QString title);
};
