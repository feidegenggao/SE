/*
 * ============================================================================
 *
 *       Filename:  url.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 20:07:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "url.h"

#include    "base/log.h"
#include    "base/types.h"
#include    "base/regex.h"

using namespace base;

const string Url::UrlRegexStr = string("^http://([^/]+)(/.*$|$)");

Url::Url(string url):str_url_(url)
{
    url_scheme_ = SCHEME_INVALID;
    if_vaild_ = false;

    if (IfFilter(url))
    {
        Analysis();
        if (url_scheme_ == SCHEME_HTTP)
        {
            Resolved();
        }
    }
}

bool Url::IsHttpUrl(const string &url)
{
    return RegexMatch(url, UrlRegexStr);
}

void Url::Analysis()
{
    //Currently, we only crwal http protocol
    if (IsHttpUrl(str_url_))
    {
        url_scheme_ = SCHEME_HTTP;
        services_ = string("http");

        RegexSearchResultType result;
        RegexSearch(str_url_, UrlRegexStr, result);
        if (result.size() > 0)
        {
            node_ = *result.begin();
        }
        if (result.size() > 1)
        {
            source_url_ = *(++result.begin());
        }
        if (source_url_.length() == 0)
        {
            source_url_ = string("/");
        }
    }
}

void Url::Resolved()
{
    AddrSet addrset_;
    DNS::GetInstance()->ResolveNodeService(node_, services_, addrset_); 
    int rt = addrset_.GetSockAddr(sockaddr_);
    if (rt == SUCCESSFUL)
    {
        /*  
           LOG_DEBUG << "node:" << node_;
           LOG_DEBUG << "services_:" << services_;
           LOG_DEBUG << "source_url_:" << source_url_;
           LOG_DEBUG << "ip:" << sockaddr_.IPStr();
           LOG_DEBUG  << "port:" << sockaddr_.PortStr();
           */
        if_vaild_ = true;
    }
}

bool Url::IfFilter(const string &url)
{
    //We only craw uestc's html
    string dst_url_regex("^http://[^/]+\\.uestc.edu.cn(/.*|$)");
    //We will not download ANY files that like a.doc b.pdf and others not html file
    string dst_url_file_doc("^http://.*\\.doc");
    string dst_url_file_pdf("^http://.*\\.pdf");
    return ( RegexMatch(url, dst_url_regex) and 
           (!RegexMatch(url, dst_url_file_doc)) and
           (!RegexMatch(url, dst_url_file_pdf)) );
}
