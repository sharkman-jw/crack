#include "str_numbers_math.h"

static inline int ctoi(char ch)
{
    return ch - '0';
}

static inline char itoc(int n)
{
    return n + '0';
}

std::string add_str_numbers_positive(const std::string& s1, const std::string& s2)
{
    if (s1.empty())
        return s2;
    if (s2.empty())
        return s1;
        
    size_t n1 = s1.length();
    size_t n2 = s2.length();
    size_t n3 = (n1 > n2 ? n1 : n2) + 1;
    std::string s3(n3, 0);
    
    size_t pos1 = n1 - 1;
    size_t pos2 = n2 - 1;
    size_t pos3 = n3 - 1;
    
    bool cont1 = true;
    bool cont2 = true;
    int sum = 0;
    int carry = 0;
    while (cont1 || cont2)
    {
        sum = carry;
        
        if (cont1)
        {
            sum += ctoi(s1[pos1]);
            if (pos1 == 0)
                cont1 = false;
            else
                -- pos1;
        }
        
        if (cont2)
        {
            sum += ctoi(s2[pos2]);
            if (pos2 == 0)
                cont2 = false;
            else
                -- pos2;
        }

        if (sum > 9)
        {
            s3[pos3--] = itoc(sum - 10);
            carry = 1;
        }
        else
        {
            s3[pos3--] = itoc(sum);
            carry = 0;
        }
    }
    
    if (carry)
    {
        s3[pos3--] = '1';
    }
    
    return pos3 == 0 ? s3.substr(1) : s3;
}