#include <iostream>
#include "fizzbuzz.h"

void fizzbuzz(size_t start, size_t n)
{
    if (0 == start)
    {
        std::cout << 0 << std::endl;
        fizzbuzz(1, n - 1);
        return;
    }
    
    int fizz = start % 3;
    if (0 == fizz)
        fizz = 3;
    int buzz = start % 5;
    if (0 == buzz)
        buzz = 5;
        
    size_t end = start + n;
    bool fizzbuzzed = false;
    for (size_t i = start; i < end; ++ i, ++ fizz, ++ buzz)
    {
        fizzbuzzed = false;
        if (fizz == 3)
        {
            std::cout << "fizz";
            fizzbuzzed = true;
            fizz = 0;
        }
        if (buzz == 5)
        {
            std::cout << "buzz";
            fizzbuzzed = true;
            buzz = 0;
        }
        if (!fizzbuzzed)
            std::cout << i;
        std::cout << std::endl;
    }
}

#ifdef THIS_IS_MAIN
int main()
{
    fizzbuzz(0, 100);
    return 0;
}
#endif
