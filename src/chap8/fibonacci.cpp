#include <vector>
#include <iostream>
#include "fibonacci.h"

unsigned int fibonacci(size_t n)
{
    if (0 == n)
        return 0;
    if (n < 3)
        return 1;
    unsigned int a = 1;
    unsigned int b = 1;
    unsigned int c = 0;
    for (size_t i = 2; i < n; ++ i)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

void print_fibonacci_series(size_t n)
{
    if (0 == n)
        return;
    size_t n1 = n + 1;
    std::vector<unsigned int> fibos(n < 3 ? 3 : n1);
    std::cout << 1 << std::endl;
    if (1 == n)
        return;
    std::cout << 1 << std::endl;
    if (2 == n)
        return;
    fibos[0] = 0;
    fibos[1] = 1;
    fibos[2] = 1;
    unsigned int val = 0;
    for (size_t i = 3; i < n1; ++ i)
    {
        val = fibos[i - 2] + fibos[i - 1];
        fibos[i] = val;
        std::cout << val << std::endl;
    }
}

void print_fibonacci_series2(size_t n)
{
    if (0 == n)
        return;
    std::cout << 1 << std::endl;
    if (1 == n)
        return;
    std::cout << 1 << std::endl;
    if (2 == n)
        return;
    unsigned int a = 1;
    unsigned int b = 1;
    unsigned int c = 0;
    size_t n1 = n + 1;
    for (size_t i = 3; i < n1; ++ i)
    {
        c = a + b;
        std::cout << c << std::endl;
        a = b;
        b = c;
    }
}
