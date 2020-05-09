#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace RegExps {
    #include <QRegExp>
     const QRegExp regEx0_1Decimal = QRegExp("^(0(\\.[0-9]{1,4})?|1(\\.0{1,4})?)$");
     const QRegExp regExInt_greaterThan0 = QRegExp("^[1-9][0-9]*$");
}

#define GET_VARIABLE_NAME(Variable) (#Variable)

#endif // CONSTANTS_H
