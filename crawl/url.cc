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
using namespace base;

void Url::Analysis()
{
    //get url_scheme_
}

void Url::Resolution()
{
    LOG_DEBUG << "url:" << str_url_;
    //TODO
    //use dns resolution the url and get addrinfo stored addr in socket_addr
    //
}
