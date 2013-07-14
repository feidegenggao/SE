/*
 * ============================================================================
 *
 *       Filename:  dns.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/14/13 09:33:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     DNS_HEADER
#define     DNS_HEADER
#include    "base/singleton.h"
using base::Singleton;

#include    <string>
using std::string;

class AddrInfo;
class DNS : public Singleton<DNS>
{
    public:
        //we store the addr info into addrinfo ( type is AddrInfo)
        //we will free the memory in AddrInfo's destructer
        void GetAddrInfoList(string node, string service, AddrInfo &addrinfo);

    private:
        void ResolutionHostName(struct addrinfo *dst_addrinfo, string host, string service);
};

class AddrInfo
{
    friend class DNS;
    public:
        AddrInfo();
        ~AddrInfo();

        struct addrinfo * GetAddrInfo();

    private:
        void SetAddrInfoPointer(struct addrinfo *addrinfo_rt);

        struct addrinfo *addrinfo_;
        struct addrinfo *current_pointer_to_addrinfo_;
};
#endif
