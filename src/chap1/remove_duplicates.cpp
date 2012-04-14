#include <iostream>
#include <tr1/unordered_set>
#include "remove_duplicates.h"

// Version 1: without using any additional memory

char* remove_duplicate_chars(char* s)
{
    if (NULL == s || 0 == *s)
        return s;
    
    const char* p1 = s; // Walker for unique part
    char* p2 = s; // Updater
    ++ p2;
    const char* p3 = p2; // Walker for rest part
    
    char ch = *p3;
    bool unique = true;
    while (ch)
    {
        // Check if current char was already in the unique section
        p1 = s;
        unique = true;
        while (p1 < p2)
        {
            if (*p1 == ch)
            {
                unique = false;
                break;
            }
            ++ p1;
        }
        
        if (unique)
            *p2++ = ch;
        
        // Move to next
        ch = *(++p3);
    }
    *p2 = 0;
    
    return s;
}

char* remove_duplicate_chars2(char* s)
{
    if (NULL == s || 0 == *s)
        return s;
    
    char* p2 = s; // Updater
    ++ p2;
    const char* p1 = p2; // Walker
    std::tr1::unordered_set<char> chars;
    chars.insert(*s);
    
    char ch = *p1;
    while (ch)
    {
        if (chars.find(ch) == chars.end()) // Not hit yet
        {
            chars.insert(ch);
            *p2++ = ch;
        }
        
        ch = *(++p1);
    }
    *p2 = 0; // Set ending
    
    return s;
}

