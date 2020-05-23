#ifndef FOCUSAWARELINEEDIT_H
#define FOCUSAWARELINEEDIT_H

#include <QLineEdit>

class FocusAwareLineEdit : public QLineEdit
{
  Q_OBJECT

public:
  FocusAwareLineEdit(QWidget *parent = 0);
  ~FocusAwareLineEdit();

signals:
  void focussed(bool hasFocus);

protected:
  virtual void focusInEvent(QFocusEvent *e);
  virtual void focusOutEvent(QFocusEvent *e);
};

#endif // FOCUSAWARELINEEDIT_H
