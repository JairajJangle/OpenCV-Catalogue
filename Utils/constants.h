#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace RegExps {
    #include <QRegExp>
     const QRegExp regEx0_1Decimal = QRegExp("^(0(\\.[0-9]{1,4})?|1(\\.0{1,4})?)$");
}

#define GET_VARIABLE_NAME(Variable) (#Variable)

#endif // CONSTANTS_H
