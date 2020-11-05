#ifndef STRING_ALLOCATION_H
#define STRING_ALLOCATION_H

#include <memory>

// Utility functions

/// Creates a std::shared_ptr<unsigned char> containing a wide string. (demo)
std::shared_ptr<unsigned char> allocWString(const wchar_t* pString, size_t& outSize);

/// Creates a std::shared_ptr<unsigned char> containing a string. (demo)
std::shared_ptr<unsigned char> allocString(const char* pString, size_t& outSize);

#endif // STRING_ALLOCATION_H
