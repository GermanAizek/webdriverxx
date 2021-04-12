/*
 *
 * Copyrights
 * Name Polfosol [https://github.com/polfosol]
 * (author bs64 encode and decode)
 *
 * Herman Semenov <GermanAizek@yandex.ru> [https://github.com/GermanAizek]
 * (port to C and minimize header)
 *
 */

#ifdef USE_STD
#include <string>
using namespace std;
#else
#define WORD_SIZE (sizeof(unsigned long))
#define WORD_MASK (WORD_SIZE -1)

typedef unsigned long size_t;
#define string (char*)

#define b64fill(_arr, _count, _value) \
{ \
    size_t i; \
    typeof(_arr) const __arr = (_arr); \
    typeof(_count) const __count = (_count); \
    typeof(_value) const __value = (_value); \
    for (i = 0; i < __count; i++) \
      __arr[i] = __value; \
}

#endif

const size_t b64strlen(const char *str)
{
    const char *chrptr;
    const unsigned long int *lngwordptr;
    unsigned long int lngword, himagic, lomagic;

    for (chrptr = str; ((unsigned long int) chrptr & (sizeof (lngword) - 1)) != 0; ++chrptr)
        if (*chrptr == '\0')
            return chrptr - str;

    lngwordptr = (unsigned long int *) chrptr;

    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof (lngword) > 4)
    {
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }
    if (sizeof (lngword) > 8)
        return ~0u;

    for (;;)
    {
        lngword = *lngwordptr++;

        if (((lngword - lomagic) & ~lngword & himagic) != 0)
        {
            const char *cp = (const char *) (lngwordptr - 1);

            if (cp[0] == 0)
                return cp - str;
            if (cp[1] == 0)
                return cp - str + 1;
            if (cp[2] == 0)
                return cp - str + 2;
            if (cp[3] == 0)
                return cp - str + 3;
            if (sizeof (lngword) > 4)
            {
                if (cp[4] == 0)
                    return cp - str + 4;
                if (cp[5] == 0)
                    return cp - str + 5;
                if (cp[6] == 0)
                    return cp - str + 6;
                if (cp[7] == 0)
                    return cp - str + 7;
            }
        }
    }
}

static const char* B64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int B64index[256] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  62, 63, 62, 62, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,  0,  0,  0,  63,
    0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

string b64encode(const void* data, const size_t &len)
{
#ifdef USE_STD
    string result((len + 2) / 3 * 4, '=');
#else
    char* result;
    result = (char*)malloc(sizeof(char) * len);
    if (result == NULL)
        exit(1);
    b64fill(result, (len + 2) / 3 * 4, '=');
#endif

    char *p = (char*) data, *str = &result[0];
    size_t j = 0, pad = len % 3;
    const size_t last = len - pad;

    for (size_t i = 0; i < last; i += 3)
    {
        int n = int(p[i]) << 16 | int(p[i + 1]) << 8 | p[i + 2];
        str[j++] = B64chars[n >> 18];
        str[j++] = B64chars[n >> 12 & 0x3F];
        str[j++] = B64chars[n >> 6 & 0x3F];
        str[j++] = B64chars[n & 0x3F];
    }
    if (pad)  /// Set padding
    {
        int n = --pad ? int(p[last]) << 8 | p[last + 1] : p[last];
        str[j++] = B64chars[pad ? n >> 10 & 0x3F : n >> 2];
        str[j++] = B64chars[pad ? n >> 4 & 0x03F : n << 4 & 0x3F];
        str[j++] = pad ? B64chars[n << 2 & 0x3F] : '=';
    }
    //std::cout << result << '\n';
    //char* ret = result;
    //free(result);
    return result;
}

string b64decode(const void* data, const size_t &len)
{
    if (len == 0) return "";

    unsigned char *p = (unsigned char*) data;
    size_t j = 0,
        pad1 = len % 4 || p[len - 1] == '=',
        pad2 = pad1 && (len % 4 > 2 || p[len - 2] != '=');
    const size_t last = (len - pad1) / 4 << 2;
#ifdef USE_STD
    string result(last / 4 * 3 + pad1 + pad2, '\0');
#else
    char* result;
    result = (char*)malloc(sizeof(char) * len);
    if (result == NULL)
        exit(1);
    b64fill(result, last / 4 * 3 + pad1 + pad2, '\0');
#endif
    unsigned char *str = (unsigned char*) &result[0];

    for (size_t i = 0; i < last; i += 4)
    {
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
        str[j++] = n >> 16;
        str[j++] = n >> 8 & 0xFF;
        str[j++] = n & 0xFF;
    }
    if (pad1)
    {
        int n = B64index[p[last]] << 18 | B64index[p[last + 1]] << 12;
        str[j++] = n >> 16;
        if (pad2)
        {
            n |= B64index[p[last + 2]] << 6;
            str[j++] = n >> 8 & 0xFF;
        }
    }
    return result;
}

const string b64encode(const string str)
{
#ifdef USE_STD
    return b64encode(str.c_str(), str.size());
#else
    char* b64str = b64encode(str, b64strlen(str));
    return b64str;
#endif
}

const string b64decode(const string str64)
{
#ifdef USE_STD
    return b64decode(str64.c_str(), str64.size());
#else
    char* b64str = b64decode(str64, b64strlen(str64));
    return b64str;
#endif
}
