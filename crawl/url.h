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
#include    "dns.h"
#include    "net/sock_addr.h"

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
        string GetSourceDataUrl() const { return source_url_;}
        string GetNode() const { return node_;}
        bool IfValid() const { return (if_vaild_ and (url_scheme_ == SCHEME_HTTP));}
        const SockAddr& GetSockAddr() const { return sockaddr_;}
        static const string UrlRegexStr;
        static bool IsHttpUrl(const string &url);
    private:
        string str_url_;
        void Analysis();
        void Resolved();
        //true:can access
        //false:can't access
        bool IfFilter(const string &url);

        UrlScheme url_scheme_;
        string node_;
        string services_;
        string source_url_;
        bool if_vaild_;
        //the first sockaddr in AddrSet
        SockAddr sockaddr_;
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
