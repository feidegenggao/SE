/*
 * ============================================================================
 *
 *       Filename:  test_dns.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/14/13 20:29:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "crawl/dns.h"

#include    "base/log.h"
#include    "base/types.h"
using namespace base;

#include    <arpa/inet.h>
#include    <string.h>
#include    <assert.h>
#include    <netdb.h>
void PrintAddrInfo(struct sockaddr_in addr_struct)
{
    const int MAXIPLEN = 50;
    char tempbuf[MAXIPLEN];
    memset(tempbuf, 0, sizeof(tempbuf));
    const char *rt = inet_ntop(AF_INET, &addr_struct.sin_addr, tempbuf, sizeof(tempbuf));
    assert(rt != NULL);
    string ipaddr(tempbuf);
    LOG_DEBUG << "result's ip:" << ipaddr;
    LOG_DEBUG << "result's port:" << ntohs(addr_struct.sin_port);
}

void PrintAddrInfo(struct addrinfo *result)
{
    if (result == NULL) return;
    const int MAXIPLEN = 50;
    char tempbuf[MAXIPLEN];
    memset(tempbuf, 0, sizeof(tempbuf));
    struct sockaddr_in addr_struct;
    memcpy(&addr_struct, result->ai_addr, sizeof(addr_struct));
    const char *rt = inet_ntop(result->ai_family, &addr_struct.sin_addr, tempbuf, sizeof(tempbuf));
    assert(rt != NULL);
    string ipaddr(tempbuf);
    LOG_DEBUG << "result's ip:" << ipaddr;
    LOG_DEBUG << "result's port:" << ntohs(addr_struct.sin_port);
}

int main()
{
    AddrInfo temp_addr_info;
    DNS::GetInstance()->ResolveNodeService("www.uestc.edu.cn", "http", temp_addr_info);

    struct sockaddr_in result;
    do
    {
        int rt = temp_addr_info.GetAddrInfo(result);
        if (rt == SUCCESSFUL)
            PrintAddrInfo(result);
        else
            break;
    }while(true);


    LOG_DEBUG << "end\n";
    return 0;
}
