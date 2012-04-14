#include <iostream>
#include "test_anagram.h"

// Assume inputs contains only a-zA-Z and spaces
bool test_anagram(const char* s1, const char* s2)
{
    if (NULL == s1 || NULL == s2)
        return false;
    
    int counts[26];
    // Init counts
    for (int i = 0; i < 26; ++ i)
        counts[i] = 0;
    
    // Process
    const char* p1 = s1;
    const char* p2 = s2;
    char ch1 = *p1;
    char ch2 = *p2;
    int offset = 0;
    while (ch1 || ch2)
    {
        if (ch1)
        {
            offset = ch1 - 'a';
            if (offset < 26 && offset >= 0)
            {
                counts[offset] ++;
            }
            else
            {
                offset = ch1 - 'A';
                if (offset < 26 && offset >= 0)
                {
                    counts[offset] ++;
                }
            }
            ch1 = *(++p1);
        }
        
        if (ch2)
        {
            offset = ch2 - 'a';
            if (offset < 26 && offset >= 0)
            {
                counts[offset] --;
            }
            else
            {
                offset = ch2 - 'A';
                if (offset < 26 && offset >= 0)
                {
                    counts[offset] --;
                }
            }
            ch2 = *(++p2);
        }
    }
    
    // Check counts
    for (int i = 0; i < 26; ++ i)
    {
        //ch1 = 'a' + i;
        //std::cout << ch1 << ' ' << counts[i] << std::endl;
        if (counts[i] != 0)
            return false;
    }
    
    return true;
}
