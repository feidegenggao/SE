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
            SockAddr(){}
            explicit SockAddr(uint16_t port);
            explicit SockAddr(const struct sockaddr_in &sockaddr):sockaddr_in_(sockaddr){}
            SockAddr(const string &ipaddr, uint16_t port);

            string IPStr() const;
            string PortStr() const;
            int    PortNum() const;
            struct sockaddr_in GetStructSockaddrIn() const
            { return sockaddr_in_;}
            void SetStructSockAddrIn(const struct sockaddr_in &sockaddr)
            { sockaddr_in_ = sockaddr;}

        private:
            void init();
            void ConvertToSockAddr(const string &ipaddr, uint16_t port);
            
        private:
            struct sockaddr_in sockaddr_in_;
    };
}
#endif
