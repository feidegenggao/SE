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
namespace net
{
class SockAddr;
enum SocketStatus
{
    INIT,
    CONNECTED,
    INVALID
};

    class Socket
    {
        public:
            Socket();
            ~Socket();
//            explicit Socket(int sockfd):sockfd_(sockfd){}
            SocketStatus Status() const { return sock_st_;}
            bool Connect(const SockAddr &server_addr);
            ssize_t Read(void *buf, size_t count);
            ssize_t Write(const void *buf, size_t count);

        private:
            /* const  */int sockfd_;
            SocketStatus sock_st_;
    };
}
#endif
