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
using namespace base;

#include    <arpa/inet.h>
#include    <strings.h>
#include    <assert.h>
#include    <netdb.h>
int main()
{
    AddrInfo temp_addr_info;
    DNS::GetInstance()->GetAddrInfoList("baidu.com", "nfs", temp_addr_info);

    struct addrinfo *temp = temp_addr_info.GetAddrInfo();
    assert(temp != NULL);

    const int MAXIPLEN = 50;
    char tempbuf[MAXIPLEN];
    bzero(tempbuf, sizeof(tempbuf));
    const char *rt = inet_ntop(temp->ai_family, temp->ai_addr, tempbuf, sizeof(tempbuf));
    assert(rt != NULL);
    LOG_DEBUG << "Addr:" << tempbuf;


    LOG_DEBUG << "end";
    return 0;
}
