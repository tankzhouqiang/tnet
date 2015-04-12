#ifndef TNET_STRINGUTIL_H
#define TNET_STRINGUTIL_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(util);

class StringUtil
{
public:
    StringUtil();
    ~StringUtil();
public:
    static std::vector<std::string> split(const std::string& text, 
            const std::string &sep, bool ignoreEmpty = true);
    
private:
    StringUtil(const StringUtil &);
    StringUtil& operator=(const StringUtil &);
public:

private:
};

TNET_TYPEDEF_PTR(StringUtil);

TNET_END_NAMESPACE(util);

#endif //TNET_STRINGUTIL_H
