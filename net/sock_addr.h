/*
 * ============================================================================
 *
 *       Filename:  socket_addr.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 19:32:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     NET_SOCKET_ADDR_HEADER
#define     NET_SOCKET_ADDR_HEADER
#include    <string>
using std::string;
#include    <netinet/in.h>

namespace net
{
    class SockAddr
    {
        public:
            SockAddr();
            explicit SockAddr(struct sockaddr_in sockaddr);
            SockAddr(string ipaddr, string port);

            string IPStr() const { return ipaddr_;}
            string PortStr() const { return port_;}
            struct sockaddr_in GetStructSockaddrIn() const { return sockaddr_in_;}
            void SetStructSockAddrIn(struct sockaddr_in sockaddr) { sockaddr_in_ = sockaddr;ConvertSockAddrToString();}

        private:
            void init();
            void ConvertSockAddrToString();
            void ConvertStringToSockAddr();
            
        private:
            string ipaddr_;
            string port_;
            struct sockaddr_in sockaddr_in_;
    };
}
#endif
