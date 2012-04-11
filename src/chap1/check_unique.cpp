#include "check_unique.h"
#if _WIN32 || _WIN64
// Windows Includes Here
#include <unordered_set>
//#error Can't be compiled on Windows yet
#else
#include <tr1/unordered_set>
#endif

bool test_unique_chars(const char* s)
{
	if (NULL == s)
		return true;

	std::tr1::unordered_set<char> chars;
	const char* p = s;
	char ch = *p;
	while (ch)
	{
		if (chars.find(ch) == chars.end())
			chars.insert(ch);
		else
			return false;
		ch = *(++p);
	}
	return true;
}
