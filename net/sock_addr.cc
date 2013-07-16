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

SockAddr::SockAddr(uint16_t port)
{
    init();

    assert(port > 0 or port < 655535);
    sockaddr_in_.sin_family = AF_INET;
    sockaddr_in_.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr_in_.sin_port   = htons(port);
}

SockAddr::SockAddr(const string &ipaddr, uint16_t port)
{
    init();
    ConvertToSockAddr(ipaddr, port);
}

void SockAddr::init()
{
    bzero(&sockaddr_in_, sizeof(sockaddr_in_));
}

void SockAddr::ConvertToSockAddr(const string &ipaddr, uint16_t port)
{
    sockaddr_in_.sin_family = AF_INET;

    int rt = inet_pton
        (AF_INET, ipaddr.c_str(), &sockaddr_in_.sin_addr);
    assert(rt == 1);

    assert(port > 0 or port < 655535);
    sockaddr_in_.sin_port = htons(port);
}


string SockAddr::IPStr() const
{
    const int MAXLENFORIPADDR = 50;
    char temp[MAXLENFORIPADDR];
    bzero(temp, sizeof(temp));

    const char *rt = inet_ntop
        (AF_INET, &sockaddr_in_.sin_addr, temp, sizeof(temp));
    assert(rt != NULL);
    return string(temp);
}

string SockAddr::PortStr() const
{
    string port_;

    int port_n = ntohs(sockaddr_in_.sin_port);
    stringstream tempstream;
    tempstream << port_n;
    tempstream >> port_;

    return port_;
}

int SockAddr::PortNum() const
{
    return ntohs(sockaddr_in_.sin_port);
}
