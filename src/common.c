#include "common.h"

// returns the length of a string s
// \n is part of the length
long long StringLen(char *s) {
    char *c = s;

    while(*c++ != '\0')
        ;

    return c - s;
}

bool StringCmp(char *s1, char *s2) {
    int cnt = 0;

    while(*s1 == *s2 && *s1 != '\0' && *s2 != '\0' && *s1 != '\n' && *s2 != '\n') {
        cnt++;
        s1++;
        s2++;
    }

    if(cnt == 0) {
        return 0;
	}

    if(*s1 == *s2) {
        return 1;
	}
	else {
        return 0;
	}
}

void StringCpy(char *dst, char *src, size_t dst_len) {
	for(int i = 0; i < dst_len - 1; i++) {
		dst[i] = src[i];
	}

	dst[dst_len] = '\0';
}

bool CharBelongsToText(char c) {
	if((c >= 32) && (c <= 126)) {
		return true;
	}
	else {
		return false;
	}
}

int CharToInt(char *s) {
	int result = 0;

	long long str_len = StringLen(s) - 1;
	int base = pow(10, str_len - 1);
	
	for(int i = 0; i < str_len; i++) {
		result += (s[i] - '0') * base;
		base /= 10;
	}

	return result;
}
