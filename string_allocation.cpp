#include "string_allocation.h"

#include <cstring>

std::shared_ptr<unsigned char> allocWString( const wchar_t* pString, size_t& outSize )
{

    size_t strSize = wcslen(pString);

    outSize = (strSize * sizeof(wchar_t)) + 2;

    std::shared_ptr<unsigned char> outString(new unsigned char[outSize], [](unsigned char * ptr){ delete [] ptr; });

    wcscpy((wchar_t*)outString.get(), pString);

    return outString;

}

std::shared_ptr<unsigned char> allocString( const char* pString, size_t& outSize )
{

    size_t strSize = strlen(pString);

    outSize = (strSize * sizeof(char)) + 1;

    std::shared_ptr<unsigned char> outString(new unsigned char[outSize], [](unsigned char * ptr){ delete [] ptr; });

    strcpy((char*)outString.get(), pString);

    return outString;

}
