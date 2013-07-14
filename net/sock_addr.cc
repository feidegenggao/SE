/*
 * ============================================================================
 *
 *       Filename:  socket_addr.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 19:54:48
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

#include    "net/sock_addr.h"
using namespace net;

#include    <sstream>
using std::stringstream;
#include    <strings.h>
#include    <assert.h>
#include    <arpa/inet.h>

#include    <stdlib.h>

SockAddr::SockAddr(struct sockaddr_in sock_addr)
{
    init();

    sockaddr_in_ = sock_addr;
    ConvertSockAddrToString();
}

SockAddr::SockAddr(string ipaddr, string port)
{
    init();

    ipaddr_ = ipaddr;
    port_ = port;
    ConvertStringToSockAddr();
}

void SockAddr::init()
{
    bzero(&sockaddr_in_, sizeof(struct sockaddr_in));
}

void SockAddr::ConvertSockAddrToString()
{
    const int MAXLENFORIPADDR = 50;
    char temp[MAXLENFORIPADDR];
    bzero(temp, sizeof(temp));

    const char *rt = inet_ntop
        (AF_INET, &sockaddr_in_.sin_addr, temp, sizeof(temp));
    assert(rt != NULL);
    ipaddr_ = string(temp);

    int port_n = ntohs(sockaddr_in_.sin_port);
    assert(port_n > 0 or port_n < 655535);
    stringstream tempstream;
    tempstream << port_n;
    tempstream >> port_;
}

void SockAddr::ConvertStringToSockAddr()
{
    sockaddr_in_.sin_family = AF_INET;

    int rt = inet_pton
        (AF_INET, ipaddr_.c_str(), &sockaddr_in_.sin_addr);
    assert(rt == 1);

    int port_n = atoi(port_.c_str());
    assert(port_n > 0 or port_n < 655535);
    sockaddr_in_.sin_port = htons(port_n);
}
