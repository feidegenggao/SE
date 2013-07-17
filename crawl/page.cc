/*
 * ============================================================================
 *
 *       Filename:  page.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 20:02:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "page.h"
#include    "http.h"
#include    "base/log.h"
using namespace base;
#include    "net/socket.h"
using namespace net;


Page::Page(const Url &url):url_(url)
{

}

void Page::VisitUrl()
{
    if (!url_.IfValid()) return;
    //Only when the url_ is valid , we will visit the url_
    LOG_DEBUG << "visit url";
    string http_header;
    string http_data;
    GetPage(url_, http_header, http_data);
}

void Page::GetUnvisitedUrl(UrlSet &unvisited_sites)
{
    if (!url_.IfValid()) return;
    Url url_temp("http://gr.uestc.edu.cn/index.shtml");
    unvisited_sites.insert(url_temp);
    LOG_DEBUG << "get unvisited url";
}
