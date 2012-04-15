#include <string>
#include "check_rotation.h"

bool is_rotation(const char* s1, const char* s2)
{
    if (NULL == s1 || NULL == s2 || 0 == *s1 || 0 == *s2)
        return false;
    std::string s1s1(s1);
    s1s1 += s1;
    return s1s1.find(s2) != std::string::npos;
}
