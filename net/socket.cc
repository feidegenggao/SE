/*
 * ============================================================================
 *
 *       Filename:  socket.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 19:26:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "net/socket.h"
#include    <assert.h>
#include    <sys/socket.h>

using namespace net;
Socket::Socket()
{
    sockfd_ = socket(AF_INET, SOCKET_STREAM, 0);
    assert(sockfd_ > 0);
}

Socket::Socket(int domain, int type, int protocol)
{
    sockfd_ = socket(domain, type, protocol);
    assert(sockfd_ > 0);
}

int Socket::connect(const socket_addr &addr)
{

}
