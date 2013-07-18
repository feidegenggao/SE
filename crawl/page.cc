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
#include    "base/tools.h"
#include    "base/regex.h"
#include    "base/log.h"
using namespace base;
#include    "net/socket.h"
using namespace net;

#include    <assert.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
Page::Page(const Url &url):url_(url)
{

}

void Page::VisitUrl()
{
    if (!url_.IfValid()) return;
    if (!GetPage(url_, http_header_, html_data_))
    {
        LOG_ERROR << "GetPage failed";
        return;
    }

    const string raw_data = html_data_;
    string raw_header("version:0.1");
    raw_header = raw_header + "url:" + url_.Str();
    raw_header = raw_header + "date:" + Timestamp::now().toFormattedString();
    raw_header = raw_header + "ip:" + url_.GetSockAddr().IPStr();
    raw_header = raw_header + "raw_data_length:" + Convert<string, size_t>(raw_data.length());

    //raw_header_length:raw_header.length()
    string raw_header_length("raw_header_length:");
    raw_header_length += Convert<string, size_t>(raw_header.length());
    write(raw_file_fd_, raw_header_length.c_str(), raw_header_length.length());

    //RawHeader
    write(raw_file_fd_, raw_header.c_str(), raw_header.length());

    //raw_data_length:raw_data.length()
    string raw_data_length("raw_data_length:");
    raw_data_length += Convert<string, size_t>(raw_data.length());
    write(raw_file_fd_, raw_data_length.c_str(), raw_data_length.length());

    //RawData
    write(raw_file_fd_, raw_data.c_str(), raw_data.length());
}

void Page::GetUnvisitedUrl(UrlSet &unvisited_sites)
{
    if (!url_.IfValid()) return;
    if (http_header_.length() == 0 or html_data_.length() == 0) return;

    //Analysis the html_data to get url that not visited

    stringstream html_stream;
    html_stream << html_data_;
    string html_temp_line;
    while(getline(html_stream, html_temp_line))
    {
        string find_url_regex(".*<a.*href=\"([^\"]*)\".*>.*</a>.*");
        RegexSearchResultType result;
        RegexSearch(html_temp_line, find_url_regex, result);
        if (result.size() > 0)
        {
            string url_temp_str = *result.begin();
            LOG_DEBUG << "url_temp_str:" << url_temp_str;
        }
    }
    //Analysis end

    Url url_temp("http://gr.uestc.edu.cn/admin");
    unvisited_sites.insert(url_temp);
    LOG_DEBUG << "get unvisited url";
}

int Page::raw_file_fd_ = OpenRawFile();
int Page::OpenRawFile()
{
    string raw_file_name = Timestamp::now().toFormattedString();
    size_t blank_opsition = raw_file_name.find(" ");
    while (blank_opsition != string::npos)
    {
        raw_file_name[blank_opsition] = '_';
        blank_opsition = raw_file_name.find(" ", blank_opsition + 1);
    }

    raw_file_name += ".raw";

    LOG_DEBUG << "raw_file_name:" << raw_file_name;

    int fd = open(raw_file_name.c_str(), O_CREAT | O_RDWR | O_TRUNC, S_IRUSR);
    assert(fd != -1);

    return fd;
}
/*
   raw file was consited of one or more RawSegments. 
   Every RawSegment consists of the follwring parts

//START
//raw_header_length: length of RawHeader 
//NOT INCLUDE segment of raw_header_length:num_a 's length
raw_header_length:num_a
RawHeader
//raw_header_length: length of RawData
//NOT INCLUDE segment of raw_data_length:num_b 's length
raw_data_length:num_b
RawData
//END

NOTE:IN REALY RawSegment THERE IS NO '\n' EXISTS.

RawHeader:
//START
//raw file format's version
version:0.1
//Next raw_data's url
url:http://www.uestc.edu.cn/index.html
//Time of when Crawl url
date:2013-07-18 15:46:49.146141
//ip corresponding the url
ip:202.112.14.184
//END

NOTE:IN REALY RawHeader THERE IS NO '\n' EXISTS.
*/
