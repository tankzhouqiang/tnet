#include <tnet/util/StringUtil.h>

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

TNET_END_NAMESPACE(util);

