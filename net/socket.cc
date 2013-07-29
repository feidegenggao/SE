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
#include    <sys/types.h>

using namespace net;
Socket::Socket():LISTEN_BACKLOG(0)
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

Socket::Socket(int accept_fd):LISTEN_BACKLOG(0),sockfd_(accept_fd)
{
    sock_st_ = CONNECTED;
}

Socket::Socket(const SockAddr &listen_addr):LISTEN_BACKLOG(1024)
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
    assert(sock_st_ == INIT);
    
    struct sockaddr_in listen_addr_socket_in = listen_addr.GetStructSockaddrIn();
    int bind_rt = bind(sockfd_, (const struct sockaddr *) (&listen_addr_socket_in),
          sizeof(listen_addr_socket_in));
    assert(bind_rt == 0);

    sock_st_ = BIND;
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

int Socket::Listen()
{
    assert(sock_st_ == BIND and LISTEN_BACKLOG > 0);
    int listen_rt = listen(sockfd_, LISTEN_BACKLOG);
    assert(listen_rt == 0);

    sock_st_ = LISTENING;
    return 0;
}

int Socket::Accept()
{
    assert(sock_st_ == LISTENING);
    int accept_fd = accept(sockfd_, NULL, NULL);
    return accept_fd;
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
