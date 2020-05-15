#ifndef UTILS_H
#define UTILS_H

#include <cmath>

namespace Numeric {
// extern:
double setPrecision(double number, int decimalPlaces);
// inline:
inline double setPrecision(double number, int decimalPlaces)
{
    int n = (int)(number *pow(10, decimalPlaces));
    return ((double)n) / pow(10, decimalPlaces);
}
}

#endif // UTILS_H
