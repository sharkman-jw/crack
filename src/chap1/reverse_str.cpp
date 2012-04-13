#include <iostream>
#include "reverse_str.h"

char* reverse_str(char* s)
{
    if (NULL == s || 0 == *s)
        return s;
    
    char* p2 = s;
    while (*p2) 
    {
        ++ p2;
    }
    -- p2;
    
    char* p1 = s;
    char ch;
    while (p1 < p2)
    {
        ch = *p1;
        *p1 = *p2;
        *p2 = ch;
        ++ p1;
        -- p2;
    }
    
    return s;
}
