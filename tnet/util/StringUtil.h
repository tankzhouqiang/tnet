#ifndef TNET_STRINGUTIL_H
#define TNET_STRINGUTIL_H

#include <tnet/common/Common.h>
#include <sstream>

TNET_BEGIN_NAMESPACE(util);

class StringUtil
{
public:
    StringUtil();
    ~StringUtil();
public:
    static std::vector<std::string> split(const std::string& text, 
            const std::string &sep, bool ignoreEmpty = true);
    template<typename T>
    static std::string toString(const T &x);
    static bool strToUInt32(const char* str, uint32_t& value);
private:
    StringUtil(const StringUtil &);
    StringUtil& operator=(const StringUtil &);
public:

private:
};

template<typename T>
inline std::string StringUtil::toString(const T &x) {
    std::stringstream oss;
    oss << x;
    return oss.str();    
}


TNET_TYPEDEF_PTR(StringUtil);

TNET_END_NAMESPACE(util);

#endif //TNET_STRINGUTIL_H
