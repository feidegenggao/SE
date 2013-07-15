/*
 * ============================================================================
 *
 *       Filename:  url.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 18:38:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     URL_HEADER
#define     URL_HEADER
#include    <iostream>
using std::ostream;
#include    <string>
using std::string;

enum UrlScheme
{
    SCHEME_HTTP,
    SCHEME_INVALID
};

class Url
{
    public:
        explicit Url(string url);
        string Str() const { return str_url_;}
        void Resolution();

    private:
        string str_url_;
        void Analysis();
        UrlScheme url_scheme_;


        string host_;
        string port_;
};

inline bool operator == (const Url &left, const Url &right)
{
    return left.Str() == right.Str();
}

inline bool operator < (const Url &left, const Url &right)
{
    return left.Str() < right.Str();
}

inline ostream& operator << (ostream &out, const Url &url)
{
    out << url.Str();
    return out;
}
#endif
