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
#include    "base/regex.h"

using namespace base;

Url::Url(string url):str_url_(url), url_scheme_(SCHEME_INVALID)
{
    Analysis();
}

void Url::Analysis()
{
    string src_regex("http://.*");
    if (Regex::GetInstance()->IfMatch(src_regex, str_url_))
    {
        url_scheme_ = SCHEME_HTTP;
    }
}

void Url::Resolution()
{
    LOG_DEBUG << "url:" << str_url_;
    //TODO
    //use dns resolution the url and get addrinfo stored addr in socket_addr
    //
}
