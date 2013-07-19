/*
 * ============================================================================
 *
 *       Filename:  test_url.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/13 16:37:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "crawl/url.h"
#include    "base/log.h"
using namespace base;

int main()
{
    Url url_edu("http://www.uestc.edu.cn");
    if (url_edu.IfValid()) 
    {
        LOG_DEBUG << url_edu.Str() << " is Valid ";
    }
    Url url_edu2("http://www.jwc.uestc.edu.cn/down/a.doc");
    if (url_edu2.IfValid())
    {
        LOG_DEBUG << url_edu2.Str() << " is Valid";
    }

    LOG_END;
    return 0;
}
