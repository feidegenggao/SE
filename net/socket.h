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
#include    "socket_addr.h"

namespace net
{
    class Socket
    {
        public:
            Socket();
            Socket(int domain, int type, int protocol);

        private:
            int sockfd_;
    };
}
#endif
