/*
 * ============================================================================
 *
 *       Filename:  socket.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 19:18:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_SOCKET_HEADER
#define     BASE_SOCKET_HEADER

#include    <unistd.h>
#include    "sock_addr.h"
namespace net
{
    class SockAddr;
    enum SocketStatus
    {
        INIT,
        CONNECTED,
        BIND,
        LISTENING,
        INVALID
    };

    class Socket
    {
        public:
            Socket();
            //create listen socket
            Socket(const SockAddr &listen_addr);
            //create accept socket
            Socket(int accept_fd);
            ~Socket();
            //            explicit Socket(int sockfd):sockfd_(sockfd){}
            SocketStatus Status() const { return sock_st_;}
            bool Connect(const SockAddr &server_addr);
            ssize_t Read(void *buf, size_t count);
            //timeout's unit is milliseconds 
            ssize_t Read(void *buf, size_t count, int timeout);
            ssize_t Write(const void *buf, size_t count);

        public:
            int Listen();
            int Accept();

        private:
            const int LISTEN_BACKLOG;

        private:
            /* const  */int sockfd_;
            SocketStatus sock_st_;

        private:
            Socket& operator = (const Socket&);
            Socket(const Socket&);
    };
}
#endif
