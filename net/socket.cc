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
#include    "net/sock_addr.h"
#include    <assert.h>
#include    <sys/socket.h>

using namespace net;
Socket::Socket()
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ > 0)
    {
        sock_st_ = INIT;
    }
    else
    {
        sock_st_ = INVALID;
    }
}

Socket::~Socket()
{
    close(sockfd_);
}

bool Socket::Connect(const SockAddr &server_addr)
{
    assert(sock_st_ == INIT);
#define SA struct sockaddr
    struct sockaddr_in server_addr_in = server_addr.GetStructSockaddrIn();
    int result = ::connect(sockfd_, (SA*)&server_addr_in, sizeof(server_addr_in));
    if (result == 0)
    {
        sock_st_ = CONNECTED;
        return true;
    }
    else
    {
        sock_st_ = INVALID;
        return false;
    }
}

ssize_t Socket::Read(void *buf, size_t count)
{
    assert(sock_st_ == CONNECTED);
    //set timer to read
    ssize_t read_n = read(sockfd_, buf, count);
    return read_n;
}

ssize_t Socket::Write(const void *buf, size_t count)
{
    assert(sock_st_ == CONNECTED);
    ssize_t write_n = write(sockfd_, buf, count);
    return write_n;
}
