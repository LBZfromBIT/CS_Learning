#ifndef AP_WCHAR_H
#define AP_WCHAR_H

#include <cstdio>
#include <cstdlib>
#define MAX_SITE 1024

class AP_Wchar
{
public:
    AP_Wchar();
    char fn[MAX_SITE] = {0};
    char m[MAX_SITE] = {0};
    FILE* wopen(const wchar_t* filename,const wchar_t* mode);
};

#endif // AP_WCHAR_H
