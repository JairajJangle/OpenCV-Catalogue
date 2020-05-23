#include "focusawarelineedit.h"

FocusAwareLineEdit::FocusAwareLineEdit(QWidget *parent)
    : QLineEdit(parent)
{}

FocusAwareLineEdit::~FocusAwareLineEdit()
{}

void FocusAwareLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit(focussed(true));
}

void FocusAwareLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit(focussed(false));
}
