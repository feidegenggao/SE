/*
 * ============================================================================
 *
 *       Filename:  test_page.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/13 17:06:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "crawl/page.h"
#include    "crawl/url.h"
#include    "crawl/types.h"

#include    "base/log.h"
using namespace base;
using namespace net;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        LOG_ERROR << "Usage:" << argv[0] << "url_want_to_visit";
        LOG_END;
        return -1;
    }
    //Url url_temp("http://www.uestc.edu.cn/");
    //Url url_temp("http://gr.uestc.edu.cn/index.shtml");
    Url url_temp(argv[1]);
    UrlSet url_set_temp;
    Page page_temp(url_temp);

    page_temp.VisitUrl();
    page_temp.GetUnvisitedUrl(url_set_temp);

    LOG_END;
    return 0;
}
