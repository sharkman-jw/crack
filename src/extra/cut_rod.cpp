#include <iostream>
#include <map>
#include "cut_rod.h"

unsigned int cut_rod_core(unsigned int n, unsigned int* p,
    std::map<unsigned int, unsigned int>& r)
{
    std::map<unsigned int, unsigned int>::iterator it = r.find(n);
    if (it != r.end())
        return it->second;
    
    unsigned int q = 0;
    unsigned int q1 = 0;
    unsigned int m = (n > 9 ? 10 : n) + 1;
    for (unsigned int i = 1; i < m; ++ i)
    {
        q1 = p[i] + cut_rod_core(n - i, p, r);
        if (q1 > q)
            q = q1;
    }
    r[n] = q;
    return q;
}

unsigned int cut_rod(unsigned int n)
{
    unsigned int p[11] = { 0,1,5,8,9,10,17,17,20,24,30 };
    std::map<unsigned int, unsigned int> r;
    return cut_rod_core(n, p, r);
}

#if 0
int main(int argc, char** argv)
{
    if (argc == 2)
    {
        std::cout << cut_rod(atoi(argv[1])) << std::endl;
        return 0;
    }
    for (unsigned int i = 1; i < 11; ++ i)
        std::cout << cut_rod(i) << std::endl;
    return 0;
}
#endif
