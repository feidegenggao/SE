/*
 * ============================================================================
 *
 *       Filename:  dns.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/14/13 09:37:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
using namespace base;
#include    "dns.h"

#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netdb.h>
#include    <strings.h>

#include    <errno.h>
#include    <string.h>

void DNS::GetAddrInfoList(string node, string service, AddrInfo &addrinfo)
{
    struct addrinfo *dst_addrinfo = NULL;
    ResolutionHostName(dst_addrinfo, node, service);

    addrinfo.SetAddrInfoPointer(dst_addrinfo);
}

void DNS::ResolutionHostName(struct addrinfo *dst_addrinfo, string node, string service)
{
    struct addrinfo hints;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    int rt = getaddrinfo(node.c_str(), service.c_str(), &hints, &dst_addrinfo);
    if (rt != 0)
    {
        LOG_ERR << "getaddrinfo error:" << strerror(errno);
    }
}

AddrInfo::AddrInfo():addrinfo_(NULL),current_pointer_to_addrinfo_(NULL)
{

}

AddrInfo::~AddrInfo()
{
    freeaddrinfo(addrinfo_);
}

struct addrinfo * AddrInfo::GetAddrInfo()
{
    struct addrinfo *temp = current_pointer_to_addrinfo_;
    if (current_pointer_to_addrinfo_ != NULL)
        current_pointer_to_addrinfo_ = current_pointer_to_addrinfo_->ai_next;
    return temp;
}

void AddrInfo::SetAddrInfoPointer(struct addrinfo *addrinfo_rt)
{ 
    addrinfo_ = addrinfo_rt; 
    current_pointer_to_addrinfo_ = addrinfo_;
}
