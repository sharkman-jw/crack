#include <iostream>
#include "replace_spaces.h"

std::string replace_spaces(const char* s)
{   
    if (NULL == s || 0 == *s)
        return std::string();
    
    // Count the number of spaces
    const char* p = s;
    char ch = *p;
    size_t n = 0;
    size_t len = 0;
    while (ch)
    {
        ++ len;
        if (ch == ' ')
            ++ n;
        ch = *(++p);
    }
    
    // Calcuate new string length
    size_t new_len = len + 2*n;
    
    // Write new string
    std::string s0(new_len, 0);
    char* p0 = const_cast<char*>(s0.data());
    p = s;
    ch = *p;
    while (ch)
    {
        if (ch == ' ')
        {
            *p0++ = '%';
            *p0++ = '2';
            *p0++ = '0';
        }
        else
            *p0++ = ch;
        ch = *(++p);
    }
    
    return s0;
}
