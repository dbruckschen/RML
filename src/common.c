#include "common.h"

// returns the length of a string s
// \n is part of the length
long long StringLen(char *s)
{
    /*    int len = 0;
    while(*s++ != '\0')
    {
	len++;
    }
    return len;
    */

    char *c = s;

    while(*c++ != '\0')
    {
	// empty
    }
    
    return c-s;
}

bool StringCmp(char *s1, char *s2)
{
    int cnt = 0;

    while(*s1 == *s2 && *s1 != '\0' && *s2 != '\0' && *s1 != '\n' && *s2 != '\n')
    {
        cnt++;
        s1++;
        s2++;
    }
    
    if(cnt == 0)
    {
        return 0;
    }
    
    if(*s1 == *s2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *StringConnect(char *s1, char *s2)
{
    return "Hello World";

}
