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

Url::Url(string url):str_url_(url)
{
    url_scheme_ = SCHEME_INVALID;
    if_vaild_ = false;
    Analysis();
    if (url_scheme_ == SCHEME_HTTP)
    {
        Resolved();
    }
}

void Url::Analysis()
{
    //Currently, we only crwal http protocol
    string src_regex("http://[^/]*/?");
    if (RegexMatch(str_url_, src_regex))
    {
        url_scheme_ = SCHEME_HTTP;
        services_ = string("http");
        string search_regex("http://([^/]*)/?");
        RegexSearchResultType result;
        RegexSearch(str_url_, search_regex, result);
        for (RegexSearchResultItor it = result.begin(); it != result.end(); it++)
        {
            node_ = *it;
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
        LOG_DEBUG << "node:" << node_;
        LOG_DEBUG << "services_:" << services_;
        LOG_DEBUG << "ip:" << sockaddr_.IPStr();
        LOG_DEBUG  << "port:" << sockaddr_.PortStr();
        if_vaild_ = true;
    }
}
