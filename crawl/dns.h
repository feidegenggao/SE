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
#include    "net/sock_addr.h"
using base::Singleton;
using net::SockAddr;

#include    <string>
using std::string;

class AddrSet;
class DNS : public Singleton<DNS>
{
    public:
        //we store the addr info into addrinfo ( type is AddrSet)
        //we will free the memory in AddrSet's destructer
        void ResolveNodeService(string node, string service, AddrSet &addrinfo);

    private:
        void ResolutionHostName(struct addrinfo **dst_addrinfo, string host, string service);
};

class AddrSet
{
    friend class DNS;
    public:
        AddrSet();
        ~AddrSet();

        //return value:
        //SUCCESSFUL: temp stored valid data
        //FAILED:   temp stored invalid data
        //Rreturn SockAddr that current_pointer_to_addrinfo_ point to
        //When we call GetSockAddr , the current_pointer_to_addrinfo_ will
        //point to the next SockAddr
        int GetSockAddr(SockAddr &temp);

    private:
        //Can't copy this object 
        //because the pointer of addrinfo_ and current_pointer_to_addrinfo_
        AddrSet(const AddrSet&);
        AddrSet& operator = (const AddrSet&);

    private:
        void SetAddrSetPointer(struct addrinfo *addrinfo_rt);

        struct addrinfo *addrinfo_;
        struct addrinfo *current_pointer_to_addrinfo_;
};
#endif
