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

Url::Url(string url):str_url_(url), url_scheme_(SCHEME_INVALID)
{
    if_vaild_ = false;
    Analysis();
    Resolved();
}

void Url::Analysis()
{
    string src_regex("http://.*");
    if (Regex::GetInstance()->IfMatch(src_regex, str_url_))
    {
        url_scheme_ = SCHEME_HTTP;
        services_ = string("http");
        //TODO:get node info use Regex
        node_ = string("www.uestc.edu.cn");
    }
}

void Url::Resolved()
{
    LOG_DEBUG << "url:" << str_url_;
    AddrSet addrset_;
    DNS::GetInstance()->ResolveNodeService(node_, services_, addrset_); 
    int rt = addrset_.GetSockAddr(sockaddr_);
    if (rt == SUCCESSFUL)
    {
        LOG_DEBUG << "Url:" << str_url_ << "'s ip:" << sockaddr_.IPStr()
                 << "\t port:" << sockaddr_.PortStr();
        if_vaild_ = true;
    }
}
