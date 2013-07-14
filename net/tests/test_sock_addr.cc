/*
 * ============================================================================
 *
 *       Filename:  test_sock_addr.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/14/13 18:08:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "net/sock_addr.h"
using namespace net;
#include    "base/log.h"

#include    <strings.h>
#include    <arpa/inet.h>
using namespace base;

int main()
{
    struct sockaddr_in first_addr;

    //init first_addr
    bzero(&first_addr, sizeof(struct sockaddr_in));
    first_addr.sin_family = AF_INET;
    first_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "192.168.13.88", &first_addr.sin_addr);
    
    SockAddr first_socket_addr(first_addr);
    LOG_INFO << "first_socket_addr's ip :" << first_socket_addr.IPStr();
    LOG_INFO << "first_socket_addr's port:" << first_socket_addr.PortStr();

    SockAddr second_socket_addr(first_socket_addr.IPStr(), first_socket_addr.PortStr());
    //SockAddr second_socket_addr("192.168.13.88", "8080");
    LOG_INFO << "second_socket_addr's ip:" << second_socket_addr.IPStr();
    LOG_INFO << "second_socket_addr's port:" << second_socket_addr.PortStr();

    SockAddr third_socket_addr(second_socket_addr.StructSockaddrIn());
    LOG_INFO << "third_socket_addr's ip:" << third_socket_addr.IPStr();
    LOG_INFO << "third_socket_addr's port:" << third_socket_addr.PortStr();


    LOG_INFO << "END\n";
    return 0;
}
