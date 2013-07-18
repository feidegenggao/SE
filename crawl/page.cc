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

string Convert(int a)
{
    stringstream temp_stream;
    temp_stream << a;
    string result;
    temp_stream >> result;

    return result;
}

void Page::VisitUrl()
{
    if (!url_.IfValid()) return;
    LOG_DEBUG << "visit url";
    GetPage(url_, http_header_, html_data_);
    string raw_header("version:0.1\n");
    raw_header = raw_header + "url:" + url_.Str() + '\n';
    raw_header = raw_header + "date:" + Timestamp::now().toFormattedString() + '\n';
    raw_header = raw_header + "ip:" + url_.GetSockAddr().IPStr() + '\n';
    raw_header = raw_header + "length:" + Convert(html_data_.length());
}

void Page::GetUnvisitedUrl(UrlSet &unvisited_sites)
{
    if (!url_.IfValid()) return;
    if (http_header_.length() == 0 or html_data_.length() == 0) return;




//    Url url_temp("http://gr.uestc.edu.cn/index.shtml");
//    unvisited_sites.insert(url_temp);
//    LOG_DEBUG << "get unvisited url";
}
