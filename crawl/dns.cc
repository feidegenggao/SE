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
#include    "base/types.h"
#include    "base/log.h"
using namespace base;
#include    "dns.h"

#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netdb.h>
#include    <strings.h>

#include    <string.h>
#include    <string>
using std::string;

void DNS::ResolveNodeService(string node, string service, AddrSet &addrinfo)
{
    struct addrinfo *dst_addrinfo = NULL;
    ResolutionHostName(&dst_addrinfo, node, service);

    addrinfo.SetAddrSetPointer(dst_addrinfo);
}

void DNS::ResolutionHostName(struct addrinfo **dst_addrinfo, string node, string service)
{
    struct addrinfo hints;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int rt = getaddrinfo(node.c_str(), service.c_str(), &hints, dst_addrinfo);
    if (rt != 0)
    {
        LOG_ERROR << "getaddrinfo error:" << gai_strerror(rt);
    }
}

AddrSet::AddrSet():addrinfo_(NULL),current_pointer_to_addrinfo_(NULL)
{

}

AddrSet::~AddrSet()
{
    freeaddrinfo(addrinfo_);
}

int AddrSet::GetSockAddr(SockAddr &temp)
{
    if (current_pointer_to_addrinfo_ != NULL)
    {
        struct sockaddr_in temp_sockaddr_in;
        memset(&temp_sockaddr_in, 0, sizeof(struct sockaddr_in));
        memcpy(&temp_sockaddr_in, current_pointer_to_addrinfo_->ai_addr, current_pointer_to_addrinfo_->ai_addrlen);

        temp.SetStructSockAddrIn(temp_sockaddr_in);
        current_pointer_to_addrinfo_ = current_pointer_to_addrinfo_->ai_next;
        return SUCCESSFUL;
    }
    return FAILED;
}

void AddrSet::SetAddrSetPointer(struct addrinfo *addrinfo_rt)
{ 
    addrinfo_ = addrinfo_rt; 
    current_pointer_to_addrinfo_ = addrinfo_;
}
