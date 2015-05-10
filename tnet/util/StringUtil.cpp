#include <tnet/util/StringUtil.h>
#include <limits>

using namespace std;

TNET_BEGIN_NAMESPACE(util);

StringUtil::StringUtil() { 
}

StringUtil::~StringUtil() { 
}

vector<string> StringUtil::split(const string& text, const string &sep, 
                                 bool ignoreEmpty)
{
    vector<string> vec;
    size_t n = 0, old = 0;
    while (n != string::npos)
    {
        n = text.find(sep,n);
        if (n != string::npos)
        {
            if (!ignoreEmpty || n != old) 
                vec.push_back(text.substr(old, n-old));
            n += sep.length();
            old = n;
        }
    }

    if (!ignoreEmpty || old < text.length()) {
        vec.push_back(text.substr(old, text.length()));
    }
    return vec;
}

bool StringUtil::strToUInt32(const char* str, uint32_t& value) 
{
    if (NULL == str || *str == 0 || *str == '-') 
    {
        return false;
    }
    char* endPtr = NULL;
    errno = 0;

# if __WORDSIZE == 64
    uint64_t value64 = strtoul(str, &endPtr, 10);
    if (value64 > std::numeric_limits<uint32_t>::max())
    {
        return false;
    }
    value = (int32_t)value64;
# else
    value = (uint32_t)strtoul(str, &endPtr, 10);
# endif

    if (errno == 0 && endPtr && *endPtr == 0) 
    {
        return true;
    }
    return false;
}

TNET_END_NAMESPACE(util);

