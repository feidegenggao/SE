/*
 * ============================================================================
 *
 *       Filename:  test_getaddrinfo.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/13 09:17:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    <arpa/inet.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netdb.h>

#include    <string.h>
#include    <errno.h>

#include    <iostream>
using namespace std;

int main()
{
    struct addrinfo hints;
    //sizeof(hints) is what???
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    struct addrinfo *result = NULL;
    string node("www.uestc.edu.cn");
    string service("http");
    int rt = getaddrinfo(node.c_str(), service.c_str(), &hints, &result);
    if (rt != 0)
    {
        cout << "getAddrinfo error" << strerror(errno) << endl;
    }

    if (result)
    {
        cout << "result's ai_family:" << result->ai_family << endl;
        char tempbuf[50];
        memset(tempbuf, 0, sizeof(tempbuf));
        struct sockaddr_in addr_struct;
        memcpy(&addr_struct, result->ai_addr, sizeof(addr_struct));
        inet_ntop(result->ai_family, &addr_struct.sin_addr, tempbuf, sizeof(tempbuf));
        string ipaddr(tempbuf);
        cout << "result's ip:" << ipaddr << endl;
    }
    else
    {
        cout << "result is NULL" << endl;
    }

    return 0;
}
