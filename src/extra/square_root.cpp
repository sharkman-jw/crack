#include <stdexcept>
#include <cmath>
#include <iostream>
#include "square_root.h"

double square_root(double num)
{
    if (num < 0.0)
        throw std::runtime_error("No real square root for negative number!");
    
    static const double epsilon = 0.0000001;
    if (std::fabs(num) < epsilon)
        return 0.0;
    
    double x0 = num;
    double x1 = 0.0;
    while (true)
    {
        x1 = 0.5*(x0 + num/x0);
        if (std::fabs(x1 - x0) < epsilon)
            break;
        x0 = x1;
    }
    
    return x1;
}