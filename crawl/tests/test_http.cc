/*
 * ============================================================================
 *
 *       Filename:  test_http.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/26/13 16:12:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
using namespace base;

#include    "crawl/url.h"
#include    "crawl/dns.h"
#include    "crawl/http.h"
using namespace net;
int main()
{
    Url dst_url("http://press.uestc.edu.cn/");

    string http_header;
    string html_data;
    LOG_DEBUG << "Start GetPage:";
    if (GetPage(dst_url, http_header, html_data))
    {
        LOG_DEBUG << "GetPage success, http_header:" << http_header
            << "html_data'length:" << html_data;
    }
    else
    {
        LOG_DEBUG << "GetPage failed";
    }

    LOG_END;
    return 0;
}
